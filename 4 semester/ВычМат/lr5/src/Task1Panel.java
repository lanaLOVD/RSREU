import javax.swing.*;
import javax.swing.border.TitledBorder;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public class Task1Panel extends ModernPanel {
    private JTextField x0Field, y0Field, xEndField, hField;
    private JTable resultTable;
    private DefaultTableModel tableModel;
    private GraphPanel graphPanel;
    private JLabel errorLabel;
    private JTextArea infoArea;

    public Task1Panel() {
        initComponents();
    }

    private void initComponents() {
        // Верхняя панель с информацией о задании
        JPanel infoPanel = createCard("📐 Задание 1: Задача Коши для ОДУ первого порядка", PRIMARY_COLOR);
        infoArea = new JTextArea();
        infoArea.setEditable(false);
        infoArea.setFont(new Font("Segoe UI", Font.PLAIN, 13));
        infoArea.setBackground(CARD_BG);
        infoArea.setText(
                "Уравнение: y' sin(x) = y ln(y)\n" +
                        "Начальное условие: y(π/2) = e\n" +
                        "Отрезок интегрирования: [π/2, π]\n" +
                        "Метод: Рунге-Кутта 4-го порядка с постоянным шагом\n" +
                        "Оценка погрешности: по формуле Рунге"
        );
        infoPanel.add(infoArea, BorderLayout.CENTER);

        // Панель ввода параметров
        JPanel inputPanel = new JPanel(new GridBagLayout());
        inputPanel.setBackground(CARD_BG);
        inputPanel.setBorder(BorderFactory.createTitledBorder(
                BorderFactory.createLineBorder(PRIMARY_COLOR),
                "Параметры вычислений",
                TitledBorder.LEFT,
                TitledBorder.TOP,
                new Font("Segoe UI", Font.BOLD, 13),
                PRIMARY_COLOR
        ));

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 10, 5, 10);
        gbc.fill = GridBagConstraints.HORIZONTAL;

        // Параметры по умолчанию
        gbc.gridx = 0; gbc.gridy = 0;
        inputPanel.add(createLabel("x₀ (начальное):"), gbc);
        gbc.gridx = 1;
        x0Field = createStyledTextField(String.valueOf(Math.PI / 2), 10);
        inputPanel.add(x0Field, gbc);

        gbc.gridx = 0; gbc.gridy = 1;
        inputPanel.add(createLabel("y₀ (начальное):"), gbc);
        gbc.gridx = 1;
        y0Field = createStyledTextField(String.valueOf(Math.E), 10);
        inputPanel.add(y0Field, gbc);

        gbc.gridx = 0; gbc.gridy = 2;
        inputPanel.add(createLabel("x_end (конечное):"), gbc);
        gbc.gridx = 1;
        xEndField = createStyledTextField(String.valueOf(Math.PI), 10);
        inputPanel.add(xEndField, gbc);

        gbc.gridx = 0; gbc.gridy = 3;
        inputPanel.add(createLabel("Шаг h:"), gbc);
        gbc.gridx = 1;
        hField = createStyledTextField("0.05", 10);
        inputPanel.add(hField, gbc);

        // Кнопка вычисления
        gbc.gridx = 0; gbc.gridy = 4;
        gbc.gridwidth = 2;
        JButton calcButton = createStyledButton("🔬 Вычислить", PRIMARY_COLOR);
        calcButton.addActionListener(e -> calculate());
        inputPanel.add(calcButton, gbc);

        // Метка для ошибки
        gbc.gridy = 5;
        errorLabel = new JLabel("Погрешность: не вычислена");
        errorLabel.setFont(new Font("Segoe UI", Font.BOLD, 14));
        errorLabel.setForeground(WARNING_COLOR);
        inputPanel.add(errorLabel, gbc);

        // Таблица результатов
        JPanel tablePanel = createCard("📋 Результаты вычислений", SUCCESS_COLOR);
        String[] columns = {"i", "x", "y (шаг h)", "y (шаг h/2)", "y (шаг 2h)", "Погрешность Рунге"};
        tableModel = new DefaultTableModel(columns, 0) {
            @Override
            public boolean isCellEditable(int row, int column) {
                return false;
            }
        };
        resultTable = new JTable(tableModel);
        resultTable.setFont(new Font("Segoe UI", Font.PLAIN, 12));
        resultTable.setRowHeight(25);
        resultTable.getTableHeader().setFont(new Font("Segoe UI", Font.BOLD, 12));
        resultTable.getTableHeader().setBackground(PRIMARY_COLOR);
        resultTable.getTableHeader().setForeground(Color.WHITE);

        JScrollPane scrollPane = new JScrollPane(resultTable);
        scrollPane.setPreferredSize(new Dimension(600, 200));
        tablePanel.add(scrollPane, BorderLayout.CENTER);

        // Панель графика
        graphPanel = new GraphPanel("y' sin(x) = y ln(y)", "x", "y");
        graphPanel.setPreferredSize(new Dimension(600, 400));

        // Компоновка
        JPanel leftPanel = new JPanel(new BorderLayout(10, 10));
        leftPanel.setBackground(BG_COLOR);
        leftPanel.add(infoPanel, BorderLayout.NORTH);
        leftPanel.add(inputPanel, BorderLayout.CENTER);
        leftPanel.add(tablePanel, BorderLayout.SOUTH);

        JSplitPane splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, leftPanel, graphPanel);
        splitPane.setDividerLocation(550);
        splitPane.setResizeWeight(0.5);

        add(splitPane, BorderLayout.CENTER);
    }

    private void calculate() {
        try {
            double x0 = Double.parseDouble(x0Field.getText());
            double y0 = Double.parseDouble(y0Field.getText());
            double xEnd = Double.parseDouble(xEndField.getText());
            double h = Double.parseDouble(hField.getText());

            if (xEnd <= x0) {
                showError("Конечное значение x должно быть больше начального!");
                return;
            }

            if (h <= 0) {
                showError("Шаг должен быть положительным!");
                return;
            }

            // Определяем правую часть уравнения
            java.util.function.BiFunction<Double, Double, Double> f = (x, y) -> {
                if (Math.abs(Math.sin(x)) < 1e-10) return 0.0;
                return y * Math.log(Math.abs(y)) / Math.sin(x);
            };

            // Решения с разными шагами
            int n = (int)((xEnd - x0) / h);
            double[][] resultH = RKMethod.solve(x0, y0, h, n, f);

            int nHalf = (int)((xEnd - x0) / (h/2));
            double[][] resultHalfH = RKMethod.solve(x0, y0, h/2, nHalf, f);

            int nDouble = (int)((xEnd - x0) / (2*h));
            double[][] result2H = RKMethod.solve(x0, y0, 2*h, nDouble, f);

            // Очищаем таблицу
            tableModel.setRowCount(0);

            // Заполняем таблицу (показываем каждый N-й шаг для шага h)
            int step = Math.max(1, n / 50); // Показываем не более 50 точек

            double maxError = 0;
            for (int i = 0; i < resultH.length; i += step) {
                int indexHalf = i * 2; // Соответствующий индекс в resultHalfH
                int index2H = i / 2;   // Соответствующий индекс в result2H

                double yH = resultH[i][1];
                double yHalfH = (indexHalf < resultHalfH.length) ? resultHalfH[indexHalf][1] : yH;
                double y2H = (index2H < result2H.length) ? result2H[index2H][1] : yH;

                // Оценка погрешности по формуле Рунге
                double error = Math.abs(yH - y2H) / 15.0;
                maxError = Math.max(maxError, error);

                tableModel.addRow(new Object[]{
                        i,
                        String.format("%.4f", resultH[i][0]),
                        String.format("%.6f", yH),
                        String.format("%.6f", yHalfH),
                        String.format("%.6f", y2H),
                        String.format("%.2e", error)
                });
            }

            errorLabel.setText(String.format("Максимальная погрешность Рунге: %.2e", maxError));
            errorLabel.setForeground(maxError < 0.01 ? SUCCESS_COLOR : WARNING_COLOR);

            // Отображаем графики
            List<double[][]> dataList = new ArrayList<>();
            dataList.add(resultH);
            dataList.add(resultHalfH);
            dataList.add(result2H);
            graphPanel.setDataWithLegend(dataList, new String[]{"Шаг h", "Шаг h/2", "Шаг 2h"});

            showSuccess("Вычисления успешно завершены!");

        } catch (NumberFormatException e) {
            showError("Пожалуйста, введите корректные числовые значения!");
        } catch (Exception e) {
            showError("Ошибка вычислений: " + e.getMessage());
            e.printStackTrace();
        }
    }
}