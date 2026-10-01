import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;

/**
 * Практическая работа №6 — Вариант 17
 * Санкт-Петербург, Июнь («Белые ночи»)
 * Построение функций принадлежности на основе экспертных оценок
 */
public class FuzzyWeather extends JFrame {

    // ─── Универсальные множества ───────────────────────────────────────────────
    static final String[] TEMP_INT   = {"-5..0","0..5","5..10","10..15","15..20","20..25","25..30"};
    static final String[] PRECIP_INT = {"0..10","10..20","20..35","35..50","50..65","65..80","80..100"};
    static final String[] WIND_INT   = {"0..2","2..4","4..6","6..8","8..10","10..12","12..15"};
    static final String[] TERMS      = {"Низкий","Средний","Высокий"};
    static final String[] EXPERTS    = {"Метеоролог","Климатолог","Житель","Турист","Гидролог"};

    // ─── Экспертные оценки: [эксперт][терм][интервал] ─────────────────────────
    static final int[][][] TEMP_EXP = {
        {{1,1,1,0,0,0,0},{0,0,0,1,1,0,0},{0,0,0,0,0,1,1}},
        {{1,1,0,0,0,0,0},{0,1,1,1,0,0,0},{0,0,0,0,1,1,1}},
        {{1,1,1,0,0,0,0},{0,0,1,1,1,0,0},{0,0,0,0,0,1,1}},
        {{1,0,0,0,0,0,0},{0,1,1,1,1,0,0},{0,0,0,0,1,1,1}},
        {{1,1,1,0,0,0,0},{0,0,0,1,1,1,0},{0,0,0,0,0,1,1}},
    };
    static final int[][][] PRECIP_EXP = {
        {{1,1,0,0,0,0,0},{0,0,1,1,1,0,0},{0,0,0,0,0,1,1}},
        {{1,1,1,0,0,0,0},{0,0,0,1,1,0,0},{0,0,0,0,1,1,1}},
        {{1,0,0,0,0,0,0},{0,1,1,1,0,0,0},{0,0,0,1,1,1,1}},
        {{1,1,0,0,0,0,0},{0,0,1,1,1,0,0},{0,0,0,0,0,1,1}},
        {{1,1,1,0,0,0,0},{0,0,0,1,1,1,0},{0,0,0,0,0,0,1}},
    };
    static final int[][][] WIND_EXP = {
        {{1,1,0,0,0,0,0},{0,1,1,1,0,0,0},{0,0,0,1,1,1,1}},
        {{1,1,1,0,0,0,0},{0,0,1,1,0,0,0},{0,0,0,0,1,1,1}},
        {{1,1,0,0,0,0,0},{0,1,1,1,0,0,0},{0,0,0,1,1,1,1}},
        {{1,0,0,0,0,0,0},{0,1,1,1,1,0,0},{0,0,0,0,0,1,1}},
        {{1,1,1,0,0,0,0},{0,0,1,1,0,0,0},{0,0,0,0,1,1,1}},
    };

    // ─── Цветовая схема ────────────────────────────────────────────────────────
    static final Color BG       = new Color(0xF4F7FB);
    static final Color HEADER   = new Color(0x1A3A5C);
    static final Color ACCENT   = new Color(0x2E86C1);
    static final Color LOW_CLR  = new Color(0x2980B9);
    static final Color MED_CLR  = new Color(0x27AE60);
    static final Color HIGH_CLR = new Color(0xE74C3C);
    static final Color[] TERM_COLORS = {LOW_CLR, MED_CLR, HIGH_CLR};

    // ─── Вычисление степеней принадлежности ───────────────────────────────────
    static double[][] calcMu(int[][][] expertsData) {
        int K = expertsData.length;
        int T = expertsData[0].length;
        int N = expertsData[0][0].length;
        double[][] mu = new double[T][N];
        for (int j = 0; j < T; j++)
            for (int i = 0; i < N; i++) {
                int sum = 0;
                for (int k = 0; k < K; k++) sum += expertsData[k][j][i];
                mu[j][i] = (double) sum / K;
            }
        return mu;
    }

    // ══════════════════════════════════════════════════════════════════════════
    // Панель графика функций принадлежности
    // ══════════════════════════════════════════════════════════════════════════
    static class MFChartPanel extends JPanel {
        private final double[][] mu;
        private final String[] intervals;
        private final String varName;
        private final String unit;

        MFChartPanel(double[][] mu, String[] intervals, String varName, String unit) {
            this.mu = mu; this.intervals = intervals;
            this.varName = varName; this.unit = unit;
            setBackground(Color.WHITE);
            setPreferredSize(new Dimension(480, 260));
            setBorder(BorderFactory.createLineBorder(new Color(0xDDE3ED), 1));
        }

        @Override protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            Graphics2D g2 = (Graphics2D) g;
            g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

            int W = getWidth(), H = getHeight();
            int padL = 50, padR = 20, padT = 30, padB = 50;
            int cW = W - padL - padR, cH = H - padT - padB;
            int N = intervals.length;

            // Фон сетки
            g2.setColor(new Color(0xF8FAFC));
            g2.fillRect(padL, padT, cW, cH);

            // Сетка
            g2.setColor(new Color(0xE8EDF5));
            g2.setStroke(new BasicStroke(0.5f, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND,
                    0, new float[]{3, 3}, 0));
            for (int yi = 0; yi <= 5; yi++) {
                int y = padT + cH - (int)(yi * cH / 5.0);
                g2.drawLine(padL, y, padL + cW, y);
            }

            // Оси
            g2.setColor(new Color(0x555555));
            g2.setStroke(new BasicStroke(1.5f));
            g2.drawLine(padL, padT, padL, padT + cH);
            g2.drawLine(padL, padT + cH, padL + cW, padT + cH);

            // Подписи Y
            g2.setFont(new Font("SansSerif", Font.PLAIN, 10));
            g2.setColor(new Color(0x555555));
            for (int yi = 0; yi <= 5; yi++) {
                int y = padT + cH - (int)(yi * cH / 5.0);
                String label = String.format("%.1f", yi / 5.0);
                g2.drawString(label, padL - 32, y + 4);
            }

            // Подписи X
            g2.setFont(new Font("SansSerif", Font.PLAIN, 9));
            double stepX = (double) cW / (N - 1);
            for (int i = 0; i < N; i++) {
                int x = padL + (int)(i * stepX);
                String lbl = intervals[i].replace("..", "\n");
                g2.drawString(intervals[i].replace("..", "-"), x - 12, padT + cH + 14);
            }

            // Название единицы
            g2.setFont(new Font("SansSerif", Font.PLAIN, 10));
            g2.setColor(new Color(0x888888));
            g2.drawString(unit, padL + cW / 2 - 10, padT + cH + 30);

            // Кривые МФ
            g2.setStroke(new BasicStroke(2.2f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
            String[] termNames = {"Низкий", "Средний", "Высокий"};
            for (int j = 0; j < mu.length; j++) {
                g2.setColor(TERM_COLORS[j]);
                int[] xs = new int[N], ys = new int[N];
                for (int i = 0; i < N; i++) {
                    xs[i] = padL + (int)(i * stepX);
                    ys[i] = padT + cH - (int)(mu[j][i] * cH);
                }
                // Filled area
                Polygon poly = new Polygon();
                poly.addPoint(xs[0], padT + cH);
                for (int i = 0; i < N; i++) poly.addPoint(xs[i], ys[i]);
                poly.addPoint(xs[N-1], padT + cH);
                Color fill = new Color(TERM_COLORS[j].getRed(), TERM_COLORS[j].getGreen(),
                        TERM_COLORS[j].getBlue(), 40);
                g2.setColor(fill);
                g2.fill(poly);

                g2.setColor(TERM_COLORS[j]);
                for (int i = 0; i < N - 1; i++)
                    g2.drawLine(xs[i], ys[i], xs[i+1], ys[i+1]);

                // Точки
                for (int i = 0; i < N; i++) {
                    g2.fillOval(xs[i] - 4, ys[i] - 4, 8, 8);
                    // Значение μ
                    if (mu[j][i] > 0.01) {
                        g2.setFont(new Font("SansSerif", Font.BOLD, 8));
                        g2.drawString(String.format("%.1f", mu[j][i]), xs[i] - 6, ys[i] - 6);
                    }
                }
            }

            // Легенда
            g2.setFont(new Font("SansSerif", Font.BOLD, 10));
            int lx = padL + 8, ly = padT + 8;
            for (int j = 0; j < 3; j++) {
                g2.setColor(TERM_COLORS[j]);
                g2.fillRect(lx, ly + j * 16, 14, 10);
                g2.setColor(new Color(0x333333));
                g2.setFont(new Font("SansSerif", Font.PLAIN, 10));
                g2.drawString(termNames[j], lx + 18, ly + j * 16 + 9);
            }

            // Заголовок
            g2.setColor(HEADER);
            g2.setFont(new Font("SansSerif", Font.BOLD, 12));
            FontMetrics fm = g2.getFontMetrics();
            g2.drawString(varName, W/2 - fm.stringWidth(varName)/2, 18);
        }
    }

    // ══════════════════════════════════════════════════════════════════════════
    // Построение таблицы экспертов (Таблица 1)
    // ══════════════════════════════════════════════════════════════════════════
    static JTable buildExpertTable(int[][][] data, String[] intervals) {
        int K = data.length, N = intervals.length;
        String[] cols = new String[N + 2];
        cols[0] = "Эксперт"; cols[1] = "Терм";
        System.arraycopy(intervals, 0, cols, 2, N);

        Object[][] rows = new Object[K * 3][N + 2];
        for (int k = 0; k < K; k++) {
            for (int j = 0; j < 3; j++) {
                int r = k * 3 + j;
                rows[r][0] = j == 0 ? EXPERTS[k] : "";
                rows[r][1] = TERMS[j];
                for (int i = 0; i < N; i++)
                    rows[r][i + 2] = data[k][j][i];
            }
        }

        DefaultTableModel model = new DefaultTableModel(rows, cols) {
            public boolean isCellEditable(int r, int c) { return false; }
        };
        JTable table = new JTable(model);
        styleTable(table, intervals.length);
        return table;
    }

    // ══════════════════════════════════════════════════════════════════════════
    // Построение таблицы μ (Таблица 2)
    // ══════════════════════════════════════════════════════════════════════════
    static JTable buildMuTable(double[][] mu, String[] intervals) {
        int N = intervals.length;
        String[] cols = new String[N + 2];
        cols[0] = "Терм"; cols[1] = "Строка";
        System.arraycopy(intervals, 0, cols, 2, N);

        Object[][] rows = new Object[6][N + 2];
        for (int j = 0; j < 3; j++) {
            rows[j*2][0] = TERMS[j];
            rows[j*2][1] = "Σ голосов";
            rows[j*2+1][0] = "";
            rows[j*2+1][1] = "μ(u)";
            for (int i = 0; i < N; i++) {
                int sum = (int) Math.round(mu[j][i] * 5);
                rows[j*2][i+2] = sum;
                rows[j*2+1][i+2] = String.format("%.2f", mu[j][i]);
            }
        }

        DefaultTableModel model = new DefaultTableModel(rows, cols) {
            public boolean isCellEditable(int r, int c) { return false; }
        };
        JTable table = new JTable(model);
        styleTable(table, intervals.length);

        // Раскраска μ-строк
        table.setDefaultRenderer(Object.class, new DefaultTableCellRenderer() {
            @Override public Component getTableCellRendererComponent(
                    JTable t, Object val, boolean sel, boolean foc, int row, int col) {
                Component c = super.getTableCellRendererComponent(t, val, sel, foc, row, col);
                setHorizontalAlignment(CENTER);
                if (row % 2 == 1) { // μ rows
                    int term = row / 2;
                    Color tc = TERM_COLORS[term];
                    c.setBackground(new Color(tc.getRed(), tc.getGreen(), tc.getBlue(), 40));
                    c.setForeground(new Color(tc.getRed()/2, tc.getGreen()/2, tc.getBlue()/2));
                    ((JLabel)c).setFont(((JLabel)c).getFont().deriveFont(Font.BOLD));
                } else {
                    c.setBackground(row % 4 == 0 ? new Color(0xF0F6FF) : new Color(0xFAFCFF));
                    c.setForeground(Color.DARK_GRAY);
                }
                return c;
            }
        });
        return table;
    }

    static void styleTable(JTable table, int N) {
        table.setRowHeight(22);
        table.setFont(new Font("Monospaced", Font.PLAIN, 12));
        table.setGridColor(new Color(0xDDE3ED));
        table.setSelectionBackground(new Color(0xBDD7EE));
        table.getTableHeader().setFont(new Font("SansSerif", Font.BOLD, 11));
        table.getTableHeader().setBackground(HEADER);
        table.getTableHeader().setForeground(Color.WHITE);
        table.setIntercellSpacing(new Dimension(4, 1));

        // Фиксируем ширину первых двух колонок
        table.getColumnModel().getColumn(0).setPreferredWidth(100);
        table.getColumnModel().getColumn(1).setPreferredWidth(90);
        for (int i = 2; i < N + 2; i++)
            table.getColumnModel().getColumn(i).setPreferredWidth(60);

        DefaultTableCellRenderer center = new DefaultTableCellRenderer();
        center.setHorizontalAlignment(JLabel.CENTER);
        for (int i = 2; i < N + 2; i++)
            table.getColumnModel().getColumn(i).setCellRenderer(center);
    }

    // ══════════════════════════════════════════════════════════════════════════
    // Вкладка для одной переменной
    // ══════════════════════════════════════════════════════════════════════════
    static JPanel buildVarTab(int[][][] expertData, String[] intervals,
                               String varName, String unit) {
        JPanel panel = new JPanel(new BorderLayout(10, 10));
        panel.setBackground(BG);
        panel.setBorder(BorderFactory.createEmptyBorder(10, 12, 10, 12));

        double[][] mu = calcMu(expertData);

        // График МФ
        MFChartPanel chart = new MFChartPanel(mu, intervals, varName, unit);

        // Таблица 1
        JLabel lbl1 = new JLabel("Таблица 1 — Мнения экспертов (бинарные оценки)");
        lbl1.setFont(new Font("SansSerif", Font.BOLD, 12));
        lbl1.setForeground(HEADER);
        JTable t1 = buildExpertTable(expertData, intervals);
        JScrollPane sp1 = new JScrollPane(t1);
        sp1.setPreferredSize(new Dimension(700, 200));

        // Таблица 2
        JLabel lbl2 = new JLabel("Таблица 2 — Степени принадлежности μ(u)");
        lbl2.setFont(new Font("SansSerif", Font.BOLD, 12));
        lbl2.setForeground(HEADER);
        JTable t2 = buildMuTable(mu, intervals);
        JScrollPane sp2 = new JScrollPane(t2);
        sp2.setPreferredSize(new Dimension(700, 130));

        // Формула
        JLabel formula = new JLabel("<html><center>μ(u<sub>i</sub>) = <sup>1</sup>/<sub>K</sub> · Σ b<sup>k</sup><sub>ij</sub> &nbsp;|&nbsp; K = 5 экспертов &nbsp;|&nbsp; b ∈ {0, 1}</center></html>");
        formula.setFont(new Font("Serif", Font.ITALIC, 13));
        formula.setForeground(new Color(0x444444));
        formula.setHorizontalAlignment(SwingConstants.CENTER);
        formula.setBorder(BorderFactory.createCompoundBorder(
            BorderFactory.createLineBorder(new Color(0xCCDDEE), 1),
            BorderFactory.createEmptyBorder(6, 12, 6, 12)));
        formula.setBackground(new Color(0xEEF5FF));
        formula.setOpaque(true);

        JPanel left = new JPanel();
        left.setLayout(new BoxLayout(left, BoxLayout.Y_AXIS));
        left.setBackground(BG);
        left.add(lbl1); left.add(Box.createVerticalStrut(4)); left.add(sp1);
        left.add(Box.createVerticalStrut(8));
        left.add(lbl2); left.add(Box.createVerticalStrut(4)); left.add(sp2);
        left.add(Box.createVerticalStrut(6)); left.add(formula);

        JSplitPane split = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, left, chart);
        split.setDividerLocation(680);
        split.setResizeWeight(0.6);
        split.setBackground(BG);
        split.setBorder(null);
        panel.add(split, BorderLayout.CENTER);
        return panel;
    }

    // ══════════════════════════════════════════════════════════════════════════
    // Главное окно
    // ══════════════════════════════════════════════════════════════════════════
    public FuzzyWeather() {
        super("Практическая работа №6 — Вариант 17: Санкт-Петербург, Июнь");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(1200, 680);
        setLocationRelativeTo(null);

        // Заголовок
        JPanel header = new JPanel(new BorderLayout());
        header.setBackground(HEADER);
        header.setBorder(BorderFactory.createEmptyBorder(12, 18, 12, 18));

        JLabel title = new JLabel("Нечёткие функции принадлежности — Погода в Санкт-Петербурге, Июнь");
        title.setFont(new Font("SansSerif", Font.BOLD, 16));
        title.setForeground(Color.WHITE);

        JLabel sub = new JLabel("Вариант 17 · «Белые Ночи» · Температура / Осадки / Ветер · 5 экспертов · 7 интервалов");
        sub.setFont(new Font("SansSerif", Font.PLAIN, 11));
        sub.setForeground(new Color(0xAAC8E8));

        header.add(title, BorderLayout.NORTH);
        header.add(sub, BorderLayout.SOUTH);

        // Вкладки
        JTabbedPane tabs = new JTabbedPane(JTabbedPane.TOP);
        tabs.setFont(new Font("SansSerif", Font.BOLD, 13));
        tabs.setBackground(BG);

        tabs.addTab("🌡  Температура (°C)",
                buildVarTab(TEMP_EXP, TEMP_INT, "Температура воздуха", "°C"));
        tabs.addTab("🌧  Осадки (мм/мес.)",
                buildVarTab(PRECIP_EXP, PRECIP_INT, "Количество осадков", "мм/мес."));
        tabs.addTab("💨  Ветер (м/с)",
                buildVarTab(WIND_EXP, WIND_INT, "Скорость ветра", "м/с"));
        tabs.addTab("ℹ  О работе", buildInfoTab());

        getContentPane().setBackground(BG);
        getContentPane().add(header, BorderLayout.NORTH);
        getContentPane().add(tabs, BorderLayout.CENTER);
    }

    static JPanel buildInfoTab() {
        JPanel p = new JPanel(new BorderLayout());
        p.setBackground(BG);
        p.setBorder(BorderFactory.createEmptyBorder(20, 30, 20, 30));

        String html = "<html><body style='font-family:serif; font-size:13px; color:#1A3A5C;'>"
            + "<h2>Практическая работа №6 — Вариант 17</h2>"
            + "<b>Регион:</b> Санкт-Петербург &nbsp;|&nbsp; <b>Месяц:</b> Июнь &nbsp;|&nbsp;"
            + " <b>Специфика:</b> «Белые ночи» (+12..+18°C, слабый ветер, умеренные осадки)<br><br>"
            + "<b>Цель:</b> построить функции принадлежности для лингвистических переменных "
            + "«температура», «осадки», «скорость ветра» на основе экспертных оценок.<br><br>"
            + "<b>Нечёткие переменные и их шкалы:</b><br>"
            + "<ul>"
            + "<li><b>Температура:</b> 7 интервалов от -5 до +30°C, шаг 5°C</li>"
            + "<li><b>Осадки:</b> 7 интервалов от 0 до 100 мм/мес.</li>"
            + "<li><b>Ветер:</b> 7 интервалов от 0 до 15 м/с, шаг ~2 м/с</li>"
            + "</ul>"
            + "<b>Термы:</b> «Низкий», «Средний», «Высокий»<br><br>"
            + "<b>Формула расчёта степени принадлежности:</b><br>"
            + "<blockquote>μ(u<sub>i</sub>) = (1/K) · Σ b<sup>k</sup><sub>ij</sub></blockquote>"
            + "где K=5 — число экспертов, b ∈ {0,1} — бинарная оценка k-го эксперта.<br><br>"
            + "<b>Эксперты:</b> Метеоролог, Климатолог, Местный житель, Турист, Гидролог<br><br>"
            + "<b>Аппроксимирующие функции принадлежности:</b><br>"
            + "<ul>"
            + "<li>Крайние термы («Низкий», «Высокий») — <b>трапецеидальная МФ</b></li>"
            + "<li>Средний терм — <b>треугольная МФ</b> или <b>гауссова</b> (σ оптимальна)</li>"
            + "</ul>"
            + "<hr>"
            + "<small>Санкт-Петербург, июнь: ср. температура +16°C, осадки ~52 мм, ветер ~3.6 м/с</small>"
            + "</body></html>";

        JEditorPane ep = new JEditorPane("text/html", html);
        ep.setEditable(false);
        ep.setBackground(new Color(0xFAFCFF));
        ep.setBorder(BorderFactory.createCompoundBorder(
            BorderFactory.createLineBorder(new Color(0xCCDDEE), 1),
            BorderFactory.createEmptyBorder(16, 20, 16, 20)));

        p.add(new JScrollPane(ep), BorderLayout.CENTER);
        return p;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            try { UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName()); }
            catch (Exception ignored) {}
            new FuzzyWeather().setVisible(true);
        });
    }
}
