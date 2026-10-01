public class RKMethod {

    // Метод Рунге-Кутты 4-го порядка для одного уравнения
    public static double[][] solve(double x0, double y0, double h, int n,
                                   java.util.function.BiFunction<Double, Double, Double> f) {
        double[][] result = new double[n + 1][2];
        double x = x0;
        double y = y0;

        result[0][0] = x;
        result[0][1] = y;

        for (int i = 0; i < n; i++) {
            double k1 = h * f.apply(x, y);
            double k2 = h * f.apply(x + h/2, y + k1/2);
            double k3 = h * f.apply(x + h/2, y + k2/2);
            double k4 = h * f.apply(x + h, y + k3);

            y = y + (k1 + 2*k2 + 2*k3 + k4) / 6;
            x = x + h;

            result[i + 1][0] = x;
            result[i + 1][1] = y;
        }

        return result;
    }

    // Метод Рунге-Кутты 4-го порядка для системы уравнений
    public static double[][] solveSystem(double x0, double[] y0, double h, int n,
                                         java.util.function.BiFunction<Double, double[], double[]> f) {
        double[][] result = new double[n + 1][3]; // x, y1, y2
        double x = x0;
        double[] y = y0.clone();

        result[0][0] = x;
        result[0][1] = y[0];
        result[0][2] = y[1];

        for (int i = 0; i < n; i++) {
            double[] k1 = multiply(f.apply(x, y), h);
            double[] k2 = multiply(f.apply(x + h/2, addArrays(y, multiply(k1, 0.5))), h);
            double[] k3 = multiply(f.apply(x + h/2, addArrays(y, multiply(k2, 0.5))), h);
            double[] k4 = multiply(f.apply(x + h, addArrays(y, k3)), h);

            for (int j = 0; j < y.length; j++) {
                y[j] = y[j] + (k1[j] + 2*k2[j] + 2*k3[j] + k4[j]) / 6;
            }
            x = x + h;

            result[i + 1][0] = x;
            result[i + 1][1] = y[0];
            result[i + 1][2] = y[1];
        }

        return result;
    }

    private static double[] multiply(double[] arr, double scalar) {
        double[] result = new double[arr.length];
        for (int i = 0; i < arr.length; i++) {
            result[i] = arr[i] * scalar;
        }
        return result;
    }

    private static double[] addArrays(double[] a, double[] b) {
        double[] result = new double[a.length];
        for (int i = 0; i < a.length; i++) {
            result[i] = a[i] + b[i];
        }
        return result;
    }

    // Оценка погрешности по формуле Рунге
    public static double estimateError(double[][] resultH, double[][] result2H, int pointIndex) {
        // Формула Рунге для метода 4-го порядка
        if (pointIndex * 2 >= resultH.length || pointIndex >= result2H.length) {
            return 0;
        }
        double yH = resultH[pointIndex * 2][1];
        double y2H = result2H[pointIndex][1];
        return Math.abs(yH - y2H) / 15.0; // 2^4 - 1 = 15
    }
}