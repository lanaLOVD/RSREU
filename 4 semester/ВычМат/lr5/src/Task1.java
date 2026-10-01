import javax.swing.*;
import javax.swing.border.TitledBorder;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public class Task1 extends ModernPanel {
    private JTextField x0Field, y0Field, xEndField, hField;
    private JTable resultTable;
    private DefaultTableModel tableModel;
    private GraphPanel graphPanel;
    private JLabel errorLabel;

    public Task1() {
        initComponents();
    }

    private void initComponents() {
        setLayout(new BorderLayout(10, 10));

        // Информационная панель
        JPanel infoPanel = createCard("Задание 1: y' sin(x) = y ln(y)", PRIMARY_COLOR);
        JTextArea infoArea = new JTextArea();
        infoArea.setEditable(false);
        infoArea.setFont(new Font("Segoe UI", Font.PLAIN, 13));
        infoArea.setBackground(CARD_BG);
        infoArea.setText(
                "Уравнение: y' sin(x) = y ln(y)\n" +
                        "Начальное условие: y(π/2) = e ≈ 2.718\n" +
                        "Отрезок: [1.57, 2.8] (далеко от сингулярности при x=π)\n" +
                        "Решение монотонно возрастает, уходя в бесконечность при x→π"
        );
        infoPanel.add(infoArea, BorderLayout.CENTER);

        // Панель ввода
        JPanel inputPanel = new JPanel(new GridBagLayout());
        inputPanel.setBackground(CARD_BG);
        inputPanel.setBorder(BorderFactory.createTitledBorder(
                BorderFactory.createLineBorder(PRIMARY_COLOR),
                "Параметры",
                TitledBorder.LEFT, TitledBorder.TOP,
                new Font("Segoe UI", Font.BOLD, 13), PRIMARY_COLOR
        ));

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 10, 5, 10);
        gbc.fill = GridBagConstraints.HORIZONTAL;

        gbc.gridx = 0; gbc.gridy = 0;
        inputPanel.add(createLabel("x₀:"), gbc);
        gbc.gridx = 1;
        x0Field = createStyledTextField("1.5708", 10);
        inputPanel.add(x0Field, gbc);

        gbc.gridx = 0; gbc.gridy = 1;
        inputPanel.add(createLabel("y₀:"), gbc);
        gbc.gridx = 1;
        y0Field = createStyledTextField("2.718282", 10);
        inputPanel.add(y0Field, gbc);

        gbc.gridx = 0; gbc.gridy = 2;
        inputPanel.add(createLabel("x_end (≤ 2.9):"), gbc);
        gbc.gridx = 1;
        xEndField = createStyledTextField("2.8", 10);
        inputPanel.add(xEndField, gbc);

        gbc.gridx = 0; gbc.gridy = 3;
        inputPanel.add(createLabel("Шаг h:"), gbc);
        gbc.gridx = 1;
        hField = createStyledTextField("0.05", 10);
        inputPanel.add(hField, gbc);

        gbc.gridx = 0; gbc.gridy = 4;
        gbc.gridwidth = 2;
        JButton calcButton = createStyledButton("Вычислить", PRIMARY_COLOR);
        calcButton.addActionListener(e -> calculate());
        inputPanel.add(calcButton, gbc);

        gbc.gridy = 5;
        errorLabel = new JLabel("Погрешность: не вычислена");
        errorLabel.setFont(new Font("Segoe UI", Font.BOLD, 13));
        errorLabel.setForeground(WARNING_COLOR);
        inputPanel.add(errorLabel, gbc);

        // Таблица
        String[] columns = {"i", "x", "y (h)", "y (h/2)", "y (2h)", "Погрешность"};
        tableModel = new DefaultTableModel(columns, 0) {
            @Override
            public boolean isCellEditable(int row, int column) { return false; }
        };
        resultTable = new JTable(tableModel);
        resultTable.setFont(new Font("Segoe UI", Font.PLAIN, 12));
        resultTable.setRowHeight(25);
        resultTable.getTableHeader().setFont(new Font("Segoe UI", Font.BOLD, 12));
        resultTable.getTableHeader().setBackground(PRIMARY_COLOR);
        resultTable.getTableHeader().setForeground(Color.WHITE);

        JScrollPane tableScroll = new JScrollPane(resultTable);
        tableScroll.setPreferredSize(new Dimension(500, 200));

        // График
        graphPanel = new GraphPanel("y' sin(x) = y ln(y)", "x", "y");

        // Компоновка
        JPanel leftPanel = new JPanel(new BorderLayout(10, 10));
        leftPanel.setBackground(BG_COLOR);
        leftPanel.add(infoPanel, BorderLayout.NORTH);
        leftPanel.add(inputPanel, BorderLayout.CENTER);
        leftPanel.add(tableScroll, BorderLayout.SOUTH);

        JSplitPane splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, leftPanel, graphPanel);
        splitPane.setDividerLocation(500);

        add(splitPane, BorderLayout.CENTER);
    }

    private void calculate() {
        try {
            double x0 = Double.parseDouble(x0Field.getText());
            double y0 = Double.parseDouble(y0Field.getText());
            double xEnd = Double.parseDouble(xEndField.getText());
            double h = Double.parseDouble(hField.getText());

            // Жёсткое ограничение
            if (xEnd > 3.0) {
                xEnd = 3.0;
                xEndField.setText("3.0");
                JOptionPane.showMessageDialog(this,
                        "x_end ограничен значением 3.0 во избежание сингулярности!",
                        "Предупреждение", JOptionPane.WARNING_MESSAGE);
            }

            if (xEnd <= x0) {
                showError("x_end должен быть больше x₀!");
                return;
            }

            if (h <= 0 || h > 0.5) {
                showError("Шаг должен быть от 0.001 до 0.5!");
                return;
            }

            // Правая часть с СИЛЬНЫМ ограничением
            java.util.function.BiFunction<Double, Double, Double> f = (x, y) -> {
                double sinX = Math.sin(x);
                if (Math.abs(sinX) < 0.01) return 0.0;

                double safeY = Math.max(0.001, Math.min(y, 10000.0));
                double logY = Math.log(safeY);
                double deriv = safeY * logY / sinX;

                // Обрезаем до разумных пределов
                return Math.max(-1000, Math.min(1000, deriv));
            };

            // Вычисления
            int n = (int)((xEnd - x0) / h);
            if (n < 5) n = 5;
            if (n > 5000) n = 5000;

            double[][] resH = RKMethod.solve(x0, y0, h, n, f);
            double[][] resH2 = RKMethod.solve(x0, y0, h/2, n*2, f);
            double[][] res2H = RKMethod.solve(x0, y0, h*2, n/2, f);

            // Таблица
            tableModel.setRowCount(0);
            int step = Math.max(1, resH.length / 25);
            double maxErr = 0;

            for (int i = 0; i < resH.length; i += step) {
                double yH = resH[i][1];
                if (Double.isNaN(yH) || Double.isInfinite(yH) || yH > 1e6) break;

                double yH2 = resH2[i*2][1];
                double y2H = res2H[i/2][1];

                double err = Math.abs(yH - y2H) / 15.0;
                if (!Double.isNaN(err)) maxErr = Math.max(maxErr, err);

                tableModel.addRow(new Object[]{
                        i,
                        String.format("%.4f", resH[i][0]),
                        String.format("%.4f", yH),
                        String.format("%.4f", yH2),
                        String.format("%.4f", y2H),
                        String.format("%.4f", err)
                });
            }

            errorLabel.setText(String.format("Макс. погрешность: %.4f", maxErr));
            errorLabel.setForeground(maxErr < 1.0 ? SUCCESS_COLOR : WARNING_COLOR);

            // График — обрезаем всё что больше 10000
            List<double[][]> dataList = new ArrayList<>();
            dataList.add(trimData(resH, 10000));
            dataList.add(trimData(resH2, 10000));
            dataList.add(trimData(res2H, 10000));
            graphPanel.setDataWithLegend(dataList, new String[]{"h=" + h, "h=" + h/2, "h=" + h*2});

            showSuccess("Готово! Показаны значения y ≤ 10000");

        } catch (NumberFormatException e) {
            showError("Введите числа правильно!");
        } catch (Exception e) {
            showError("Ошибка: " + e.getMessage());
            e.printStackTrace();
        }
    }

    private double[][] trimData(double[][] data, double maxY) {
        List<double[]> list = new ArrayList<>();
        for (double[] p : data) {
            if (Double.isFinite(p[0]) && Double.isFinite(p[1]) && p[1] >= 0 && p[1] <= maxY) {
                list.add(new double[]{p[0], p[1]});
            } else {
                break; // как только вышли за пределы — останавливаемся
            }
        }
        if (list.isEmpty()) {
            return new double[][]{{data[0][0], Math.min(data[0][1], maxY)}};
        }
        return list.toArray(new double[0][]);
    }
}