import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.List;

public class EquationSolver extends JFrame {
    private JTextField textFieldEpsilon;
    private JTextArea textAreaResults;
    private GraphPanel panelGraph;
    private JButton buttonSolve;
    private JComboBox<String> comboBoxEquation;
    private JTextField textFieldMinX, textFieldMaxX;
    private JLabel labelStatus;

    private double minX = -5;
    private double maxX = 5;
    private double scaleY = 1.0;

    public EquationSolver() {
        setTitle("Решение уравнений численными методами");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Верхняя панель с настройками
        JPanel topPanel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);

        gbc.gridx = 0; gbc.gridy = 0;
        topPanel.add(new JLabel("Выберите уравнение:"), gbc);

        gbc.gridx = 1; gbc.gridy = 0; gbc.gridwidth = 3;
        comboBoxEquation = new JComboBox<>(new String[]{
                "0. tg(x) = x (наименьший положительный)",
                "1. x⁵ – x – 0.2 = 0 (наименьший)",
                "2. x⁵ + x – 0.2 = 0 (положительный)",
                "3. e^x = 5x² (наименьший положительный)",
                "4. x⁵ – x – 0.2 = 0 (ближайший к 0)",
                "5. x³ – 10x + 2 = 0 (наименьший)",
                "6. x⁴ – x² + 5x – 10 = 0 (положительный)",
                "7. x³ – 10x + 2 = 0 (наибольший)",
                "8. e^x = 3x² (наименьший)",
                "9. x³ – 10x + 2 = 0 (ближайший к 0)"
        });
        comboBoxEquation.setPreferredSize(new Dimension(300, 25));
        topPanel.add(comboBoxEquation, gbc);

        gbc.gridx = 0; gbc.gridy = 1; gbc.gridwidth = 1;
        topPanel.add(new JLabel("Точность:"), gbc);

        gbc.gridx = 1; gbc.gridy = 1;
        textFieldEpsilon = new JTextField("0.0001", 10);
        topPanel.add(textFieldEpsilon, gbc);

        gbc.gridx = 2; gbc.gridy = 1;
        buttonSolve = new JButton("Решить");
        buttonSolve.setBackground(new Color(59, 89, 182));
        buttonSolve.setForeground(Color.WHITE);
        topPanel.add(buttonSolve, gbc);

        // Панель управления масштабом
        gbc.gridx = 0; gbc.gridy = 2; gbc.gridwidth = 1;
        topPanel.add(new JLabel("X мин:"), gbc);

        gbc.gridx = 1; gbc.gridy = 2;
        textFieldMinX = new JTextField("-5", 5);
        topPanel.add(textFieldMinX, gbc);

        gbc.gridx = 2; gbc.gridy = 2;
        topPanel.add(new JLabel("X макс:"), gbc);

        gbc.gridx = 3; gbc.gridy = 2;
        textFieldMaxX = new JTextField("5", 5);
        topPanel.add(textFieldMaxX, gbc);

        gbc.gridx = 4; gbc.gridy = 2;
        JButton buttonZoomIn = new JButton("+");
        buttonZoomIn.addActionListener(e -> zoom(0.8));
        topPanel.add(buttonZoomIn, gbc);

        gbc.gridx = 5; gbc.gridy = 2;
        JButton buttonZoomOut = new JButton("-");
        buttonZoomOut.addActionListener(e -> zoom(1.2));
        topPanel.add(buttonZoomOut, gbc);

        gbc.gridx = 6; gbc.gridy = 2;
        JButton buttonReset = new JButton("Сброс");
        buttonReset.addActionListener(e -> resetView());
        topPanel.add(buttonReset, gbc);

        add(topPanel, BorderLayout.NORTH);

        // Центральная панель с графиком и результатами
        JSplitPane splitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT);

        // Панель для графика
        panelGraph = new GraphPanel();
        panelGraph.setPreferredSize(new Dimension(900, 400));
        panelGraph.setBackground(Color.WHITE);

        // Добавляем слушатели мыши для панорамирования
        GraphMouseListener mouseListener = new GraphMouseListener();
        panelGraph.addMouseListener(mouseListener);
        panelGraph.addMouseMotionListener(mouseListener);
        panelGraph.addMouseWheelListener(mouseListener);

        JScrollPane graphScrollPane = new JScrollPane(panelGraph);
        graphScrollPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        graphScrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
        splitPane.setTopComponent(graphScrollPane);

        // Текстовая область для результатов
        textAreaResults = new JTextArea(20, 90);
        textAreaResults.setEditable(false);
        textAreaResults.setFont(new Font("Monospaced", Font.PLAIN, 12));
        JScrollPane scrollPane = new JScrollPane(textAreaResults);
        splitPane.setBottomComponent(scrollPane);

        add(splitPane, BorderLayout.CENTER);

        // Нижняя панель статуса
        labelStatus = new JLabel("Готов к работе. Выберите уравнение и нажмите 'Решить'");
        labelStatus.setBorder(BorderFactory.createEtchedBorder());
        add(labelStatus, BorderLayout.SOUTH);

        // Обработчик кнопки
        buttonSolve.addActionListener(e -> solveEquation());

        // Обработчик изменения масштаба из текстовых полей
        textFieldMinX.addActionListener(e -> updateGraphRange());
        textFieldMaxX.addActionListener(e -> updateGraphRange());

        pack();
        setLocationRelativeTo(null);
    }

    private void zoom(double factor) {
        double centerX = (minX + maxX) / 2;
        double range = (maxX - minX) * factor / 2;
        minX = centerX - range;
        maxX = centerX + range;
        updateGraphRange();
    }

    private void resetView() {
        minX = -5;
        maxX = 5;
        textFieldMinX.setText(String.valueOf(minX));
        textFieldMaxX.setText(String.valueOf(maxX));
        panelGraph.repaint();
    }

    private void updateGraphRange() {
        try {
            minX = Double.parseDouble(textFieldMinX.getText());
            maxX = Double.parseDouble(textFieldMaxX.getText());
            if (minX >= maxX) {
                throw new NumberFormatException();
            }
            panelGraph.repaint();
        } catch (NumberFormatException ex) {
            labelStatus.setText("Ошибка: некорректный диапазон X");
        }
    }

    private double f(double x) {
        int selectedIndex = comboBoxEquation.getSelectedIndex();
        switch (selectedIndex) {
            case 0: // tg(x) = x
                return Math.tan(x) - x;
            case 1: // x⁵ - x - 0.2
                return Math.pow(x, 5) - x - 0.2;
            case 2: // x⁵ + x - 0.2
                return Math.pow(x, 5) + x - 0.2;
            case 3: // e^x = 5x²
                return Math.exp(x) - 5 * x * x;
            case 4: // x⁵ - x - 0.2 (ближайший к 0)
                return Math.pow(x, 5) - x - 0.2;
            case 5: // x³ - 10x + 2 (наименьший)
                return Math.pow(x, 3) - 10 * x + 2;
            case 6: // x⁴ - x² + 5x - 10 (ВАРИАНТ 6)
                return Math.pow(x, 4) - Math.pow(x, 2) + 5 * x - 10;
            case 7: // x³ - 10x + 2 (наибольший)
                return Math.pow(x, 3) - 10 * x + 2;
            case 8: // e^x = 3x²
                return Math.exp(x) - 3 * x * x;
            case 9: // x³ - 10x + 2 (ближайший к 0)
                return Math.pow(x, 3) - 10 * x + 2;
            default:
                return 0;
        }
    }

    private double fDerivative(double x) {
        int selectedIndex = comboBoxEquation.getSelectedIndex();
        switch (selectedIndex) {
            case 0: // tg(x) - x
                return 1.0 / Math.pow(Math.cos(x), 2) - 1;
            case 1: // x⁵ - x - 0.2
            case 2: // x⁵ + x - 0.2
            case 4:
                return 5 * Math.pow(x, 4) - 1;
            case 3: // e^x - 5x²
                return Math.exp(x) - 10 * x;
            case 5: // x³ - 10x + 2
            case 7:
            case 9:
                return 3 * Math.pow(x, 2) - 10;
            case 6: // x⁴ - x² + 5x - 10
                return 4 * Math.pow(x, 3) - 2 * x + 5;
            case 8: // e^x - 3x²
                return Math.exp(x) - 6 * x;
            default:
                return 0;
        }
    }

    private double fSecondDerivative(double x) {
        int selectedIndex = comboBoxEquation.getSelectedIndex();
        switch (selectedIndex) {
            case 0: // tg(x) - x
                return 2 * Math.tan(x) / Math.pow(Math.cos(x), 2);
            case 1: // x⁵ - x - 0.2
            case 2: // x⁵ + x - 0.2
            case 4:
                return 20 * Math.pow(x, 3);
            case 3: // e^x - 5x²
                return Math.exp(x) - 10;
            case 5: // x³ - 10x + 2
            case 7:
            case 9:
                return 6 * x;
            case 6: // x⁴ - x² + 5x - 10
                return 12 * Math.pow(x, 2) - 2;
            case 8: // e^x - 3x²
                return Math.exp(x) - 6;
            default:
                return 0;
        }
    }

    // Метод дихотомии (бисекции)
    private double bisectionMethod(double a, double b, double eps) {
        textAreaResults.append("\n--- МЕТОД ДИХОТОМИИ ---\n");
        int iterations = 0;
        double c = 0;

        if (f(a) * f(b) > 0) {
            textAreaResults.append("На интервале нет гарантированного корня (функция одного знака)\n");
            return Double.NaN;
        }

        while ((b - a) > eps) {
            c = (a + b) / 2;
            if (Math.abs(f(c)) < eps) break;

            if (f(a) * f(c) <= 0) {
                b = c;
            } else {
                a = c;
            }
            iterations++;
            textAreaResults.append(String.format("Итерация %d: x = %.8f, f(x) = %.8f\n",
                    iterations, c, f(c)));

            if (iterations > 1000) break;
        }

        textAreaResults.append(String.format("Корень: %.8f\nКоличество итераций: %d\n", c, iterations));
        return c;
    }

    // Метод хорд
    private double chordMethod(double a, double b, double eps) {
        textAreaResults.append("\n--- МЕТОД ХОРД ---\n");
        int iterations = 0;
        double x = a;
        double X = b;

        if (f(a) * f(b) > 0) {
            textAreaResults.append("На интервале нет гарантированного корня\n");
            return Double.NaN;
        }

        // Выбираем неподвижную точку X по условию f(X)*f''(X) > 0
        try {
            if (f(a) * fSecondDerivative(a) > 0) {
                X = a;
                x = b;
            } else if (f(b) * fSecondDerivative(b) > 0) {
                X = b;
                x = a;
            }
        } catch (Exception e) {
            X = b;
            x = a;
        }

        double prevX;
        do {
            prevX = x;
            double fX = f(X);
            double fx = f(x);
            if (Math.abs(fX - fx) < 1e-12) break;

            x = x - fx * (X - x) / (fX - fx);
            iterations++;
            textAreaResults.append(String.format("Итерация %d: x = %.8f, f(x) = %.8f\n",
                    iterations, x, f(x)));

            if (iterations > 1000) break;
        } while (Math.abs(x - prevX) > eps && Math.abs(f(x)) > eps);

        textAreaResults.append(String.format("Корень: %.8f\nКоличество итераций: %d\n", x, iterations));
        return x;
    }

    // Метод Ньютона (касательных)
    private double newtonMethod(double a, double b, double eps) {
        textAreaResults.append("\n--- МЕТОД НЬЮТОНА ---\n");
        int iterations = 0;
        double x = a;

        // Выбираем начальное приближение
        try {
            if (f(a) * fSecondDerivative(a) > 0) {
                x = a;
            } else if (f(b) * fSecondDerivative(b) > 0) {
                x = b;
            } else {
                x = (a + b) / 2;
            }
        } catch (Exception e) {
            x = (a + b) / 2;
        }

        double prevX;
        do {
            prevX = x;
            double deriv = fDerivative(x);
            if (Math.abs(deriv) < 1e-12) break;

            x = x - f(x) / deriv;
            iterations++;
            textAreaResults.append(String.format("Итерация %d: x = %.8f, f(x) = %.8f\n",
                    iterations, x, f(x)));

            if (iterations > 1000) break;
        } while (Math.abs(x - prevX) > eps && Math.abs(f(x)) > eps);

        textAreaResults.append(String.format("Корень: %.8f\nКоличество итераций: %d\n", x, iterations));
        return x;
    }

    // Модифицированный метод Ньютона
    private double modifiedNewtonMethod(double a, double b, double eps) {
        textAreaResults.append("\n--- МОДИФИЦИРОВАННЫЙ МЕТОД НЬЮТОНА ---\n");
        int iterations = 0;
        double x = (a + b) / 2;

        double fDerivX0 = fDerivative(x);
        if (Math.abs(fDerivX0) < 1e-12) {
            textAreaResults.append("Производная близка к нулю\n");
            return Double.NaN;
        }

        double prevX;
        do {
            prevX = x;
            x = x - f(x) / fDerivX0;
            iterations++;
            textAreaResults.append(String.format("Итерация %d: x = %.8f, f(x) = %.8f\n",
                    iterations, x, f(x)));

            if (iterations > 1000) break;
        } while (Math.abs(x - prevX) > eps && Math.abs(f(x)) > eps);

        textAreaResults.append(String.format("Корень: %.8f\nКоличество итераций: %d\n", x, iterations));
        return x;
    }

    // Комбинированный метод
    private double combinedMethod(double a, double b, double eps) {
        textAreaResults.append("\n--- КОМБИНИРОВАННЫЙ МЕТОД ---\n");
        int iterations = 0;

        double x = a;
        double y = b;

        // Выбираем начальные приближения
        try {
            if (f(a) * fSecondDerivative(a) > 0) {
                x = a;
                y = b;
            } else {
                x = b;
                y = a;
            }
        } catch (Exception e) {
            x = a;
            y = b;
        }

        double prevX, prevY;
        do {
            prevX = x;
            prevY = y;

            // Шаг метода Ньютона
            double deriv = fDerivative(x);
            if (Math.abs(deriv) > 1e-12) {
                x = x - f(x) / deriv;
            }

            // Шаг метода хорд с использованием x как неподвижной точки
            double fx = f(x);
            double fy = f(y);
            if (Math.abs(fx - fy) > 1e-12) {
                y = y - fy * (x - y) / (fx - fy);
            }

            iterations++;
            double avg = (x + y) / 2;
            textAreaResults.append(String.format("Итерация %d: x=%.8f, y=%.8f, среднее=%.8f, f(среднее)=%.8f\n",
                    iterations, x, y, avg, f(avg)));

            if (iterations > 1000) break;
        } while (Math.abs(x - y) > eps && Math.abs(f((x + y) / 2)) > eps);

        double result = (x + y) / 2;
        textAreaResults.append(String.format("Корень: %.8f\nКоличество итераций: %d\n", result, iterations));
        return result;
    }

    // Метод итераций
    private double iterationMethod(double a, double b, double eps) {
        textAreaResults.append("\n--- МЕТОД ИТЕРАЦИЙ ---\n");
        int iterations = 0;

        // Находим M1 - максимум производной на отрезке
        double M1 = findMaxDerivative(a, b);
        if (M1 < 1e-12) M1 = 1.0;

        double x = (a + b) / 2;

        double prevX;
        do {
            prevX = x;
            // Итерирующая функция φ(x) = x - f(x)/M1
            x = x - f(x) / M1;
            iterations++;
            textAreaResults.append(String.format("Итерация %d: x = %.8f, f(x) = %.8f\n",
                    iterations, x, f(x)));

            if (iterations > 1000) break;
        } while (Math.abs(x - prevX) > eps && Math.abs(f(x)) > eps);

        textAreaResults.append(String.format("Корень: %.8f\nКоличество итераций: %d\n", x, iterations));
        return x;
    }

    private double findMaxDerivative(double a, double b) {
        double max = 0;
        int steps = 100;
        double step = (b - a) / steps;

        for (int i = 0; i <= steps; i++) {
            double x = a + i * step;
            try {
                double deriv = Math.abs(fDerivative(x));
                if (deriv > max) max = deriv;
            } catch (Exception e) {
                // Игнорируем точки разрыва
            }
        }
        return max;
    }

    private List<double[]> findIntervals() {
        List<double[]> intervals = new ArrayList<>();
        int selectedIndex = comboBoxEquation.getSelectedIndex();

        switch (selectedIndex) {
            case 0: // tg(x) = x
                intervals.add(new double[]{4.4, 4.6}); // Первый положительный корень
                intervals.add(new double[]{7.7, 7.9}); // Второй корень
                break;
            case 1: // x⁵ - x - 0.2
                intervals.add(new double[]{-1, 0});
                intervals.add(new double[]{0, 1});
                intervals.add(new double[]{1, 2});
                break;
            case 2: // x⁵ + x - 0.2
                intervals.add(new double[]{0, 1});
                break;
            case 3: // e^x = 5x²
                intervals.add(new double[]{-1, 0});
                intervals.add(new double[]{0, 1});
                intervals.add(new double[]{4, 5});
                break;
            case 4: // x⁵ - x - 0.2 (ближайший к 0)
                intervals.add(new double[]{-0.5, 0.5});
                break;
            case 5: // x³ - 10x + 2 (наименьший)
                intervals.add(new double[]{-4, -3});
                break;
            case 6: // x⁴ - x² + 5x - 10 (ВАРИАНТ 6 - положительный корень)
                intervals.add(new double[]{1, 2}); // Положительный корень около 1.5
                intervals.add(new double[]{-3, -2}); // Отрицательный корень
                break;
            case 7: // x³ - 10x + 2 (наибольший)
                intervals.add(new double[]{3, 4});
                break;
            case 8: // e^x = 3x²
                intervals.add(new double[]{-1, 0});
                intervals.add(new double[]{0, 1});
                intervals.add(new double[]{3, 4});
                break;
            case 9: // x³ - 10x + 2 (ближайший к 0)
                intervals.add(new double[]{0, 1});
                break;
            default:
                intervals.add(new double[]{-5, 5});
        }

        return intervals;
    }

    private void solveEquation() {
        textAreaResults.setText("");
        double eps;
        try {
            eps = Double.parseDouble(textFieldEpsilon.getText());
        } catch (NumberFormatException ex) {
            labelStatus.setText("Ошибка: некорректная точность");
            return;
        }

        // Обновляем диапазон графика
        try {
            minX = Double.parseDouble(textFieldMinX.getText());
            maxX = Double.parseDouble(textFieldMaxX.getText());
        } catch (NumberFormatException ex) {
            // Используем значения по умолчанию
        }

        // Определяем интервалы для поиска корней
        List<double[]> intervals = findIntervals();

        textAreaResults.append("========================================\n");
        textAreaResults.append("УРАВНЕНИЕ: " + comboBoxEquation.getSelectedItem() + "\n");
        textAreaResults.append("ТОЧНОСТЬ: " + eps + "\n");
        textAreaResults.append("========================================\n");

        for (double[] interval : intervals) {
            double a = interval[0];
            double b = interval[1];

            // Проверяем, есть ли корень на интервале
            if (f(a) * f(b) <= 0) {
                textAreaResults.append("\n╔════════════════════════════════════════════╗");
                textAreaResults.append(String.format("\n║ ИНТЕРВАЛ [%.2f, %.2f]                      ║", a, b));
                textAreaResults.append("\n�════════════════════════════════════════════╝");

                // Применяем все методы
                bisectionMethod(a, b, eps);
                chordMethod(a, b, eps);
                newtonMethod(a, b, eps);
                modifiedNewtonMethod(a, b, eps);
                combinedMethod(a, b, eps);
                iterationMethod(a, b, eps);
            } else {
                textAreaResults.append(String.format("\nНа интервале [%.2f, %.2f] нет корня или функция одного знака\n", a, b));
            }
        }

        // Обновляем график
        panelGraph.repaint();
        labelStatus.setText("Решение завершено. Найдено " + intervals.size() + " интервалов с корнями");
    }

    // Класс для панели графика
    class GraphPanel extends JPanel {
        private List<Double> roots = new ArrayList<>();
        private Point dragStart;

        public GraphPanel() {
            setPreferredSize(new Dimension(900, 400));
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            Graphics2D g2d = (Graphics2D) g;
            g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

            int width = getWidth();
            int height = getHeight();

            // Находим мин и макс значения функции для масштабирования по Y
            double minY = Double.MAX_VALUE;
            double maxY = -Double.MAX_VALUE;

            int steps = 1000;
            double step = (maxX - minX) / steps;

            for (int i = 0; i <= steps; i++) {
                double x = minX + i * step;
                try {
                    double y = f(x);
                    if (!Double.isNaN(y) && !Double.isInfinite(y)) {
                        minY = Math.min(minY, y);
                        maxY = Math.max(maxY, y);
                    }
                } catch (Exception e) {
                    // Игнорируем точки разрыва
                }
            }

            // Добавляем отступы
            double yRange = maxY - minY;
            if (yRange < 1e-12) yRange = 1.0;
            minY -= yRange * 0.1;
            maxY += yRange * 0.1;

            // Преобразование координат
            double scaleX = width / (maxX - minX);
            double scaleY = height / (maxY - minY);

            // Рисуем сетку
            g2d.setColor(new Color(240, 240, 240));
            for (int i = 0; i <= 10; i++) {
                int x = (int)(i * width / 10.0);
                g2d.drawLine(x, 0, x, height);

                int y = (int)(i * height / 10.0);
                g2d.drawLine(0, y, width, y);
            }

            // Рисуем оси
            g2d.setColor(Color.BLACK);
            g2d.setStroke(new BasicStroke(2));

            int originX = (int)(-minX * scaleX);
            int originY = (int)(maxY * scaleY);

            // Ось X
            if (originY >= 0 && originY < height) {
                g2d.drawLine(0, originY, width, originY);
            }

            // Ось Y
            if (originX >= 0 && originX < width) {
                g2d.drawLine(originX, 0, originX, height);
            }

            // Подписи осей
            g2d.setFont(new Font("Arial", Font.PLAIN, 12));
            g2d.drawString("X", width - 20, originY - 5);
            g2d.drawString("Y", originX + 5, 20);

            // Рисуем функцию
            g2d.setColor(Color.BLUE);
            g2d.setStroke(new BasicStroke(2));

            int prevX = -1;
            int prevY = -1;

            for (int i = 0; i <= steps; i++) {
                double x = minX + i * step;
                try {
                    double y = f(x);

                    if (!Double.isNaN(y) && !Double.isInfinite(y)) {
                        int screenX = (int)((x - minX) * scaleX);
                        int screenY = (int)((maxY - y) * scaleY);

                        if (screenX >= 0 && screenX < width && screenY >= 0 && screenY < height) {
                            if (prevX != -1 && Math.abs(screenY - prevY) < height) {
                                g2d.drawLine(prevX, prevY, screenX, screenY);
                            }
                            prevX = screenX;
                            prevY = screenY;
                        } else {
                            prevX = -1;
                        }
                    } else {
                        prevX = -1;
                    }
                } catch (Exception e) {
                    prevX = -1;
                }
            }

            // Рисуем найденные корни (если есть)
            if (!roots.isEmpty()) {
                g2d.setColor(Color.RED);
                g2d.setStroke(new BasicStroke(3));

                for (double root : roots) {
                    int screenX = (int)((root - minX) * scaleX);
                    int screenY = (int)((maxY - 0) * scaleY);

                    if (screenX >= 0 && screenX < width) {
                        g2d.fillOval(screenX - 5, screenY - 5, 10, 10);
                        g2d.drawString(String.format("%.3f", root), screenX + 5, screenY - 5);
                    }
                }
            }

            // Отображаем диапазон
            g2d.setColor(Color.DARK_GRAY);
            g2d.setFont(new Font("Arial", Font.PLAIN, 10));
            g2d.drawString(String.format("X: [%.2f, %.2f]", minX, maxX), 10, 20);
            g2d.drawString(String.format("Y: [%.2f, %.2f]", minY, maxY), 10, 35);
        }

        public void setRoots(List<Double> roots) {
            this.roots = roots;
            repaint();
        }
    }

    // Класс для обработки мыши на графике
    class GraphMouseListener extends MouseAdapter {
        private Point lastPoint;

        @Override
        public void mousePressed(MouseEvent e) {
            lastPoint = e.getPoint();
        }

        @Override
        public void mouseDragged(MouseEvent e) {
            if (lastPoint != null) {
                int dx = e.getX() - lastPoint.x;
                double range = maxX - minX;
                double deltaX = -dx * range / panelGraph.getWidth();

                minX += deltaX;
                maxX += deltaX;

                textFieldMinX.setText(String.format("%.2f", minX));
                textFieldMaxX.setText(String.format("%.2f", maxX));

                lastPoint = e.getPoint();
                panelGraph.repaint();
            }
        }

        @Override
        public void mouseWheelMoved(MouseWheelEvent e) {
            double rotation = e.getPreciseWheelRotation();
            double factor = rotation > 0 ? 1.1 : 0.9;

            double mouseX = minX + (maxX - minX) * e.getX() / panelGraph.getWidth();
            double range = (maxX - minX) * factor / 2;

            minX = mouseX - range;
            maxX = mouseX + range;

            textFieldMinX.setText(String.format("%.2f", minX));
            textFieldMaxX.setText(String.format("%.2f", maxX));

            panelGraph.repaint();
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            try {
                UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
            } catch (Exception e) {
                e.printStackTrace();
            }
            new EquationSolver().setVisible(true);
        });
    }
}