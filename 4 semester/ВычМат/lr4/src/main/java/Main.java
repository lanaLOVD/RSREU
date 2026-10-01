import javax.swing.*;
import java.awt.*;

public class Main extends JFrame {

    JTextField nField = new JTextField("4", 5);
    JTextField bField = new JTextField("0.15", 5);

    JTextArea output = new JTextArea();

    JComboBox<String> modeBox = new JComboBox<>(new String[]{"Вперед", "Назад"});

    DrawPanel drawPanel = new DrawPanel();

    double b = 0.15;
    int n = 4;
    double xmin = -10, xmax = 10;

    double[] x;
    double[][] diff;

    public Main() {
        setTitle("Лабораторная 4 -Интерполяция Ньютона");
        setSize(1100, 700);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        JPanel left = new JPanel(new BorderLayout());
        left.setPreferredSize(new Dimension(350, 700));

        JPanel input = new JPanel(new GridLayout(6, 2, 5, 5));
        input.setBorder(BorderFactory.createTitledBorder("Вход"));

        JButton calc = new JButton("ВЫЧИСЛИТЬ");

        input.add(new JLabel("n (количество точек):"));
        input.add(nField);
        input.add(new JLabel("b:"));
        input.add(bField);
        input.add(new JLabel("Метод:"));
        input.add(modeBox);
        input.add(new JLabel(""));
        input.add(calc);

        output.setEditable(false);
        JScrollPane scroll = new JScrollPane(output);
        scroll.setBorder(BorderFactory.createTitledBorder("Результат"));

        left.add(input, BorderLayout.NORTH);
        left.add(scroll, BorderLayout.CENTER);

        add(left, BorderLayout.WEST);
        add(drawPanel, BorderLayout.CENTER);

        calc.addActionListener(e -> compute());
    }

    void compute() {
        try {
            n = Integer.parseInt(nField.getText());
            b = Double.parseDouble(bField.getText());

            x = new double[n + 1];
            diff = new double[n + 1][n + 1];

            double h = (xmax - xmin) / n;

            for (int i = 0; i <= n; i++) {
                x[i] = xmin + i * h;
                diff[i][0] = f(x[i]);
            }

            for (int j = 1; j <= n; j++) {
                for (int i = 0; i <= n - j; i++) {
                    diff[i][j] = (diff[i + 1][j - 1] - diff[i][j - 1]) /
                            (x[i + j] - x[i]);
                }
            }

            output.setText("");
            for (int i = 0; i <= n; i++) {
                output.append(String.format("x=%.2f | ", x[i]));
                for (int j = 0; j <= n - i; j++) {
                    output.append(String.format("%.5f ", diff[i][j]));
                }
                output.append("\n");
            }

            drawPanel.repaint();

        } catch (Exception e) {
            JOptionPane.showMessageDialog(this, "Ошибка!");
        }
    }

    double f(double x) {
        return Math.exp(-b * x) * Math.cos(Math.PI * (x + x * x));
    }

    double newton(double X) {
        if (modeBox.getSelectedIndex() == 0) { // вперед
            double result = diff[0][0];
            double term = 1.0;
            for (int i = 1; i <= n; i++) {
                term *= (X - x[i - 1]);
                result += diff[0][i] * term;
            }
            return result;
        } else { // назад
            double result = diff[n][0];
            double term = 1.0;
            for (int i = 1; i <= n; i++) {
                term *= (X - x[n - i + 1]);
                result += diff[n - i][i] * term;
            }
            return result;
        }
    }

    class DrawPanel extends JPanel {

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);

            if (x == null) return;

            int w = getWidth();
            int h = getHeight();

            double minY = Double.MAX_VALUE;
            double maxY = -Double.MAX_VALUE;

            for (double X = xmin; X <= xmax; X += 0.01) {
                double y1 = f(X);
                double y2 = newton(X);
                double err = Math.abs(y1 - y2);

                minY = Math.min(minY, Math.min(y1, Math.min(y2, err)));
                maxY = Math.max(maxY, Math.max(y1, Math.max(y2, err)));
            }

            double scaleX = (w - 100) / (xmax - xmin);
            double scaleY = (h - 100) / (maxY - minY);

            Graphics2D g2 = (Graphics2D) g;

            // ===== СЕТКА =====
            g2.setColor(new Color(220, 220, 220));

            int steps = 10;

            for (int i = 0; i <= steps; i++) {
                int xLine = 50 + (int) ((w - 100) * i / (double) steps);
                int yLine = 50 + (int) ((h - 100) * i / (double) steps);

                g2.drawLine(xLine, 50, xLine, h - 50);
                g2.drawLine(50, yLine, w - 50, yLine);
            }

            // ===== ОСИ =====
            g2.setColor(Color.BLACK);
            g2.drawLine(50, h - 50, w - 50, h - 50);
            g2.drawLine(50, 50, 50, h - 50);

            // ===== ПОДПИСИ ОСЕЙ =====
            g2.drawString("X", w - 40, h - 30);
            g2.drawString("Y", 20, 60);

            // ===== ЧИСЛА ПО X =====
            for (int i = 0; i <= steps; i++) {
                double val = xmin + (xmax - xmin) * i / steps;
                int px = 50 + (int) ((val - xmin) * scaleX);

                g2.drawLine(px, h - 50, px, h - 45);
                g2.drawString(String.format("%.2f", val), px - 15, h - 30);
            }

            // ===== ЧИСЛА ПО Y =====
            for (int i = 0; i <= steps; i++) {
                double val = minY + (maxY - minY) * i / steps;
                int py = (int) (h - 50 - (val - minY) * scaleY);

                g2.drawLine(45, py, 50, py);
                g2.drawString(String.format("%.2f", val), 5, py + 5);
            }

            // ===== ГРАФИКИ =====
            drawGraph(g2, scaleX, scaleY, minY, true, Color.BLUE);
            drawGraph(g2, scaleX, scaleY, minY, false, Color.RED);
            drawError(g2, scaleX, scaleY, minY);
            drawPoints(g2, scaleX, scaleY, minY);

            // ===== ЛЕГЕНДА =====
            g2.setColor(Color.BLACK);
            g2.drawString("Синий — f(x)", 60, 20);
            g2.drawString("Красный — интерполяция", 200, 20);
            g2.drawString("Зеленый — ошибка", 420, 20);
        }

        void drawGraph(Graphics g, double sx, double sy, double minY, boolean real, Color c) {
            g.setColor(c);
            int px = 0, py = 0;
            boolean first = true;

            for (double X = xmin; X <= xmax; X += 0.01) {
                double Y = real ? f(X) : newton(X);

                int x1 = (int) (50 + (X - xmin) * sx);
                int y1 = (int) (getHeight() - 50 - (Y - minY) * sy);

                if (!first) g.drawLine(px, py, x1, y1);

                px = x1;
                py = y1;
                first = false;
            }
        }

        void drawError(Graphics g, double sx, double sy, double minY) {
            g.setColor(Color.GREEN.darker());
            int px = 0, py = 0;
            boolean first = true;

            for (double X = xmin; X <= xmax; X += 0.01) {
                double Y = Math.abs(f(X) - newton(X));

                int x1 = (int) (50 + (X - xmin) * sx);
                int y1 = (int) (getHeight() - 50 - (Y - minY) * sy);

                if (!first) g.drawLine(px, py, x1, y1);

                px = x1;
                py = y1;
                first = false;
            }
        }

        void drawPoints(Graphics g, double sx, double sy, double minY) {
            g.setColor(Color.BLACK);
            for (int i = 0; i <= n; i++) {
                int px = (int) (50 + (x[i] - xmin) * sx);
                int py = (int) (getHeight() - 50 - (f(x[i]) - minY) * sy);
                g.fillOval(px - 4, py - 4, 8, 8);
            }
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Main().setVisible(true));
    }
}