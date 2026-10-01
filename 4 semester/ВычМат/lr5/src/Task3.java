import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public class Task3 extends JPanel {
    private GraphPanel graphPanel;

    public Task3() {
        setLayout(new BorderLayout());

        // Панель управления
        JPanel controlPanel = new JPanel();
        JButton calculateButton = new JButton("Вычислить");
        calculateButton.addActionListener(e -> calculate());
        controlPanel.add(calculateButton);

        // Панель графика
        graphPanel = new GraphPanel(
                "Задача 3: y'' + y' + y = 0",
                "x",
                "y"
        );

        add(controlPanel, BorderLayout.NORTH);
        add(new JScrollPane(graphPanel), BorderLayout.CENTER);
    }

    private void calculate() {
        // Параметры для варианта 6
        double a1 = 1;
        double a2 = 1;
        double x0 = 0;
        double y0 = 1;
        double yPrime0 = 1;
        double xEnd = 10;
        double h = 0.1;

        // Приводим к системе первого порядка:
        // z1 = y, z2 = y'
        // z1' = z2
        // z2' = -a1*z2 - a2*z1

        double[] initialConditions = {y0, yPrime0};

        java.util.function.BiFunction<Double, double[], double[]> f = (x, z) -> {
            double[] result = new double[2];
            result[0] = z[1];
            result[1] = -a1 * z[1] - a2 * z[0];
            return result;
        };

        // Решения с разными шагами
        int n = (int)((xEnd - x0) / h);
        double[][] resultH = RKMethod.solveSystem(x0, initialConditions, h, n, f);

        n = (int)((xEnd - x0) / (h/2));
        double[][] resultH2 = RKMethod.solveSystem(x0, initialConditions, h/2, n, f);

        n = (int)((xEnd - x0) / (2*h));
        double[][] result2H = RKMethod.solveSystem(x0, initialConditions, 2*h, n, f);

        // Извлекаем только y (первую компоненту)
        List<double[][]> dataList = new ArrayList<>();
        dataList.add(extractY(resultH));
        dataList.add(extractY(resultH2));
        dataList.add(extractY(result2H));

        graphPanel.setDataWithLegend(dataList, new String[]{"Шаг h", "Шаг h/2", "Шаг 2h"});
    }

    private double[][] extractY(double[][] data) {
        double[][] result = new double[data.length][2];
        for (int i = 0; i < data.length; i++) {
            result[i][0] = data[i][0];
            result[i][1] = data[i][1]; // y
        }
        return result;
    }
}