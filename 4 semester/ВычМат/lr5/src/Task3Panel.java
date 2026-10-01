import javax.swing.*;
import javax.swing.border.TitledBorder;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public class Task3Panel extends ModernPanel {
    private JTextField a1Field, a2Field, x0Field, xEndField, hField;
    private JTextField y0Field, yPrime0Field;
    private JTable resultTable;
    private DefaultTableModel tableModel;
    private GraphPanel graphPanel;
    private JLabel errorLabel;

    public Task3Panel() {
        initComponents();
    }

    private void initComponents() {
        // Информационная панель
        JPanel infoPanel = createCard("📈 Задание 3: ОДУ второго порядка", new Color(255, 140, 0));
        JTextArea infoArea = new JTextArea();
        infoArea.setEditable(false);
        infoArea.setFont(new Font("Segoe UI", Font.PLAIN, 13));
        infoArea.setBackground(CARD_BG);
        infoArea.setText(
                "Уравнение: y'' + a₁·y' + a₂·y = 0\n" +
                        "Вариант 6: a₁ = 1, a₂ = 1\n" +
                        "Начальные условия: y(0) = 1, y'(0) = 1\n" +
                        "Метод: сведение к системе ОДУ и метод Рунге-Кутта\n" +
                        "  z₁' = z₂\n" +
                        "  z₂' = -a₁·z₂ - a₂·z₁"
        );
        infoPanel.add(infoArea, BorderLayout.CENTER);

        // Панель ввода параметров
        JPanel inputPanel = new JPanel(new GridBagLayout());
        inputPanel.setBackground(CARD_BG);
        inputPanel.setBorder(BorderFactory.createTitledBorder(
                BorderFactory.createLineBorder(WARNING_COLOR),
                "Параметры уравнения",
                TitledBorder.LEFT,
                TitledBorder.TOP,
                new Font("Segoe UI", Font.BOLD, 13),
                WARNING_COLOR
        ));

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(3, 10, 3, 10);

        gbc.gridx = 0; gbc.gridy = 0;
        inputPanel.add(createLabel("Коэффициент a₁:"), gbc);
        gbc.gridx = 1;
        a1Field = createStyledTextField("1", 10);
        inputPanel.add(a1Field, gbc);

        gbc.gridx = 0; gbc.gridy = 1;
        inputPanel.add(createLabel("Коэффициент a₂:"), gbc);
        gbc.gridx = 1;
        a2Field = createStyledTextField("1", 10);
        inputPanel.add(a2Field, gbc);

        gbc.gridx = 0; gbc.gridy = 2;
        inputPanel.add(createLabel("x₀:"), gbc);
        gbc.gridx = 1;
        x0Field = createStyledTextField("0", 10);
        inputPanel.add(x0Field, gbc);

        gbc.gridx = 0; gbc.gridy = 3;
        inputPanel.add(createLabel("x_end:"), gbc);
        gbc.gridx = 1;
        xEndField = createStyledTextField("10", 10);
        inputPanel.add(xEndField, gbc);

        gbc.gridx = 0; gbc.gridy = 4;
        inputPanel.add(createLabel("y(x₀):"), gbc);
        gbc.gridx = 1;
        y0Field = createStyledTextField("1", 10);
        inputPanel.add(y0Field, gbc);

        gbc.gridx = 0; gbc.gridy = 5;
        inputPanel.add(createLabel("y'(x₀):"), gbc);
        gbc.gridx = 1;
        yPrime0Field = createStyledTextField("1", 10);
        inputPanel.add(yPrime0Field, gbc);

        gbc.gridx = 0; gbc.gridy = 6;
        inputPanel.add(createLabel("Шаг h:"), gbc);
        gbc.gridx = 1;
        hField = createStyledTextField("0.05", 10);
        inputPanel.add(hField, gbc);

        gbc.gridx = 0; gbc.gridy = 7;
        gbc.gridwidth = 2;
        JButton calcButton = createStyledButton("🔬 Вычислить", WARNING_COLOR);
        calcButton.addActionListener(e -> calculate());
        inputPanel.add(calcButton, gbc);

        gbc.gridy = 8;
        errorLabel = new JLabel("Погрешность: не вычислена");
        errorLabel.setFont(new Font("Segoe UI", Font.BOLD, 13));
        errorLabel.setForeground(WARNING_COLOR);
        inputPanel.add(errorLabel, gbc);

        // Таблица результатов
        String[] columns = {"i", "x", "y(x)", "y'(x)", "Погрешность y"};
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
        resultTable.getTableHeader().setBackground(WARNING_COLOR);
        resultTable.getTableHeader().setForeground(Color.WHITE);

        JScrollPane tableScroll = new JScrollPane(resultTable);
        tableScroll.setPreferredSize(new Dimension(400, 200));

        // График
        graphPanel = new GraphPanel("y'' + a₁·y' + a₂·y = 0", "x", "y(x)");

        // Компоновка
        JPanel leftPanel = new JPanel(new BorderLayout(10, 10));
        leftPanel.setBackground(BG_COLOR);
        leftPanel.add(infoPanel, BorderLayout.NORTH);
        leftPanel.add(inputPanel, BorderLayout.CENTER);
        leftPanel.add(tableScroll, BorderLayout.SOUTH);

        JSplitPane splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, leftPanel, graphPanel);
        splitPane.setDividerLocation(450);

        add(splitPane, BorderLayout.CENTER);
    }

    private void calculate() {
        try {
            double a1 = Double.parseDouble(a1Field.getText());
            double a2 = Double.parseDouble(a2Field.getText());
            double x0 = Double.parseDouble(x0Field.getText());
            double xEnd = Double.parseDouble(xEndField.getText());
            double y0 = Double.parseDouble(y0Field.getText());
            double yPrime0 = Double.parseDouble(yPrime0Field.getText());
            double h = Double.parseDouble(hField.getText());

            // Система: z1 = y, z2 = y'
            java.util.function.BiFunction<Double, double[], double[]> f = (x, z) -> {
                double[] result = new double[2];
                result[0] = z[1];
                result[1] = -a1 * z[1] - a2 * z[0];
                return result;
            };

            double[] initialZ = {y0, yPrime0};

            int n = (int)((xEnd - x0) / h);
            double[][] resultH = RKMethod.solveSystem(x0, initialZ, h, n, f);
            double[][] resultHalfH = RKMethod.solveSystem(x0, initialZ, h/2, n*2, f);
            double[][] result2H = RKMethod.solveSystem(x0, initialZ, 2*h, n/2, f);

            // Заполняем таблицу
            tableModel.setRowCount(0);
            int step = Math.max(1, n / 50);

            double maxError = 0;
            for (int i = 0; i < resultH.length; i += step) {
                double error = Math.abs(resultH[i][1] - resultHalfH[i*2][1]) / 15.0;
                maxError = Math.max(maxError, error);

                tableModel.addRow(new Object[]{
                        i,
                        String.format("%.4f", resultH[i][0]),
                        String.format("%.6f", resultH[i][1]),
                        String.format("%.6f", resultH[i][2]),
                        String.format("%.2e", error)
                });
            }

            errorLabel.setText(String.format("Максимальная погрешность: %.2e", maxError));
            errorLabel.setForeground(maxError < 0.01 ? SUCCESS_COLOR : WARNING_COLOR);

            // График y(x)
            List<double[][]> dataList = new ArrayList<>();
            dataList.add(extractY(resultH));
            dataList.add(extractY(resultHalfH));
            dataList.add(extractY(result2H));

            graphPanel.setDataWithLegend(dataList, new String[]{"Шаг h", "Шаг h/2", "Шаг 2h"});

            showSuccess("Уравнение второго порядка решено!");

        } catch (NumberFormatException e) {
            showError("Пожалуйста, введите корректные числовые значения!");
        }
    }

    private double[][] extractY(double[][] data) {
        double[][] result = new double[data.length][2];
        for (int i = 0; i < data.length; i++) {
            result[i][0] = data[i][0];
            result[i][1] = data[i][1];
        }
        return result;
    }
}