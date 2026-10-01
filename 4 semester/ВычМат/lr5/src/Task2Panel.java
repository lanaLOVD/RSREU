import javax.swing.*;
import javax.swing.border.TitledBorder;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public class Task2Panel extends ModernPanel {
    private JTextField aField, bField, hField;
    private JTextField y10Field, y20Field;
    private JTable resultTable;
    private DefaultTableModel tableModel;
    private GraphPanel graphY1Panel, graphY2Panel;
    private JLabel errorLabel1, errorLabel2;

    public Task2Panel() {
        initComponents();
    }

    private void initComponents() {
        // Информационная панель
        JPanel infoPanel = createCard("📊 Задание 2: Система ОДУ первого порядка", new Color(46, 139, 87));
        JTextArea infoArea = new JTextArea();
        infoArea.setEditable(false);
        infoArea.setFont(new Font("Segoe UI", Font.PLAIN, 13));
        infoArea.setBackground(CARD_BG);
        infoArea.setText(
                "Система уравнений:\n" +
                        "  y₁' = sin(x² + y₂²)\n" +
                        "  y₂' = cos(x · y₁)\n" +
                        "Начальные условия: y₁(0) = 0, y₂(0) = 0\n" +
                        "Отрезок: [0, 4]\n" +
                        "Метод: Рунге-Кутта 4-го порядка для систем"
        );
        infoPanel.add(infoArea, BorderLayout.CENTER);

        // Панель ввода
        JPanel inputPanel = new JPanel(new GridBagLayout());
        inputPanel.setBackground(CARD_BG);
        inputPanel.setBorder(BorderFactory.createTitledBorder(
                BorderFactory.createLineBorder(SUCCESS_COLOR),
                "Параметры системы",
                TitledBorder.LEFT,
                TitledBorder.TOP,
                new Font("Segoe UI", Font.BOLD, 13),
                SUCCESS_COLOR
        ));

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 10, 5, 10);

        gbc.gridx = 0; gbc.gridy = 0;
        inputPanel.add(createLabel("a (начало отрезка):"), gbc);
        gbc.gridx = 1;
        aField = createStyledTextField("0", 10);
        inputPanel.add(aField, gbc);

        gbc.gridx = 0; gbc.gridy = 1;
        inputPanel.add(createLabel("b (конец отрезка):"), gbc);
        gbc.gridx = 1;
        bField = createStyledTextField("4", 10);
        inputPanel.add(bField, gbc);

        gbc.gridx = 0; gbc.gridy = 2;
        inputPanel.add(createLabel("y₁(a):"), gbc);
        gbc.gridx = 1;
        y10Field = createStyledTextField("0", 10);
        inputPanel.add(y10Field, gbc);

        gbc.gridx = 0; gbc.gridy = 3;
        inputPanel.add(createLabel("y₂(a):"), gbc);
        gbc.gridx = 1;
        y20Field = createStyledTextField("0", 10);
        inputPanel.add(y20Field, gbc);

        gbc.gridx = 0; gbc.gridy = 4;
        inputPanel.add(createLabel("Шаг h:"), gbc);
        gbc.gridx = 1;
        hField = createStyledTextField("0.1", 10);
        inputPanel.add(hField, gbc);

        gbc.gridx = 0; gbc.gridy = 5;
        gbc.gridwidth = 2;
        JButton calcButton = createStyledButton("🔬 Вычислить", SUCCESS_COLOR);
        calcButton.addActionListener(e -> calculate());
        inputPanel.add(calcButton, gbc);

        gbc.gridy = 6;
        errorLabel1 = new JLabel("Погрешность y₁: не вычислена");
        errorLabel1.setFont(new Font("Segoe UI", Font.BOLD, 13));
        errorLabel1.setForeground(WARNING_COLOR);
        inputPanel.add(errorLabel1, gbc);

        gbc.gridy = 7;
        errorLabel2 = new JLabel("Погрешность y₂: не вычислена");
        errorLabel2.setFont(new Font("Segoe UI", Font.BOLD, 13));
        errorLabel2.setForeground(WARNING_COLOR);
        inputPanel.add(errorLabel2, gbc);

        // Таблица результатов
        String[] columns = {"i", "x", "y₁", "y₂"};
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
        resultTable.getTableHeader().setBackground(SUCCESS_COLOR);
        resultTable.getTableHeader().setForeground(Color.WHITE);

        JScrollPane tableScroll = new JScrollPane(resultTable);
        tableScroll.setPreferredSize(new Dimension(400, 150));

        // Графики
        graphY1Panel = new GraphPanel("y₁' = sin(x² + y₂²)", "x", "y₁");
        graphY2Panel = new GraphPanel("y₂' = cos(x · y₁)", "x", "y₂");

        JPanel graphPanel = new JPanel(new GridLayout(2, 1, 5, 5));
        graphPanel.setBackground(BG_COLOR);
        graphPanel.add(graphY1Panel);
        graphPanel.add(graphY2Panel);

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
            double a = Double.parseDouble(aField.getText());
            double b = Double.parseDouble(bField.getText());
            double y10 = Double.parseDouble(y10Field.getText());
            double y20 = Double.parseDouble(y20Field.getText());
            double h = Double.parseDouble(hField.getText());

            if (b <= a) {
                showError("Конечное значение должно быть больше начального!");
                return;
            }

            // Система уравнений
            java.util.function.BiFunction<Double, double[], double[]> f = (x, y) -> {
                double[] result = new double[2];
                result[0] = Math.sin(x * x + y[1] * y[1]);
                result[1] = Math.cos(x * y[0]);
                return result;
            };

            double[] y0 = {y10, y20};

            int n = (int)((b - a) / h);
            double[][] resultH = RKMethod.solveSystem(a, y0, h, n, f);
            double[][] resultHalfH = RKMethod.solveSystem(a, y0, h/2, n*2, f);
            double[][] result2H = RKMethod.solveSystem(a, y0, 2*h, n/2, f);

            // Заполняем таблицу
            tableModel.setRowCount(0);
            int step = Math.max(1, n / 50);

            double maxError1 = 0, maxError2 = 0;

            for (int i = 0; i < resultH.length; i += step) {
                double error1 = Math.abs(resultH[i][1] - resultHalfH[i*2][1]) / 15.0;
                double error2 = Math.abs(resultH[i][2] - resultHalfH[i*2][2]) / 15.0;

                maxError1 = Math.max(maxError1, error1);
                maxError2 = Math.max(maxError2, error2);

                tableModel.addRow(new Object[]{
                        i,
                        String.format("%.4f", resultH[i][0]),
                        String.format("%.6f", resultH[i][1]),
                        String.format("%.6f", resultH[i][2])
                });
            }

            errorLabel1.setText(String.format("Макс. погрешность y₁: %.2e", maxError1));
            errorLabel1.setForeground(maxError1 < 0.01 ? SUCCESS_COLOR : WARNING_COLOR);

            errorLabel2.setText(String.format("Макс. погрешность y₂: %.2e", maxError2));
            errorLabel2.setForeground(maxError2 < 0.01 ? SUCCESS_COLOR : WARNING_COLOR);

            // Графики
            List<double[][]> dataY1 = new ArrayList<>();
            List<double[][]> dataY2 = new ArrayList<>();

            dataY1.add(extractComponent(resultH, 1));
            dataY1.add(extractComponent(resultHalfH, 1));
            dataY1.add(extractComponent(result2H, 1));

            dataY2.add(extractComponent(resultH, 2));
            dataY2.add(extractComponent(resultHalfH, 2));
            dataY2.add(extractComponent(result2H, 2));

            graphY1Panel.setDataWithLegend(dataY1, new String[]{"Шаг h", "Шаг h/2", "Шаг 2h"});
            graphY2Panel.setDataWithLegend(dataY2, new String[]{"Шаг h", "Шаг h/2", "Шаг 2h"});

            showSuccess("Система успешно решена!");

        } catch (NumberFormatException e) {
            showError("Пожалуйста, введите корректные числовые значения!");
        }
    }

    private double[][] extractComponent(double[][] data, int componentIndex) {
        double[][] result = new double[data.length][2];
        for (int i = 0; i < data.length; i++) {
            result[i][0] = data[i][0];
            result[i][1] = data[i][componentIndex];
        }
        return result;
    }
}