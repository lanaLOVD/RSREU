import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class GraphPanel extends JPanel {
    private List<double[][]> dataList;
    private String[] legendLabels;
    private String title;
    private String xLabel;
    private String yLabel;

    private Color[] curveColors = {
            new Color(70, 130, 180),
            new Color(220, 50, 50),
            new Color(50, 160, 50),
            new Color(255, 140, 0),
            new Color(128, 0, 128)
    };

    private int margin = 80;

    public GraphPanel(String title, String xLabel, String yLabel) {
        this.title = title;
        this.xLabel = xLabel;
        this.yLabel = yLabel;
        setBackground(Color.WHITE);
        setPreferredSize(new Dimension(700, 500));
        setMinimumSize(new Dimension(400, 300));
    }

    public void setDataWithLegend(List<double[][]> dataList, String[] legendLabels) {
        this.dataList = dataList;
        this.legendLabels = legendLabels;
        repaint();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2 = (Graphics2D) g;
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        g2.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_ON);

        int width = getWidth();
        int height = getHeight();

        margin = Math.max(60, Math.min(width, height) / 8);
        int graphWidth = width - 2 * margin;
        int graphHeight = height - 2 * margin;

        if (graphWidth < 100 || graphHeight < 100) return;

        if (dataList == null || dataList.isEmpty()) {
            g2.setColor(Color.GRAY);
            g2.setFont(new Font("Segoe UI", Font.ITALIC, 16));
            String msg = "Нажмите «Вычислить» для построения графика";
            FontMetrics fm = g2.getFontMetrics();
            g2.drawString(msg, (width - fm.stringWidth(msg)) / 2, height / 2);
            return;
        }

        // ========== КЛЮЧЕВОЕ ИЗМЕНЕНИЕ ==========
        // Находим границы данных, отсекая выбросы
        double xMin = Double.MAX_VALUE, xMax = Double.MIN_VALUE;
        double yMin = Double.MAX_VALUE, yMax = Double.MIN_VALUE;

        // Собираем все Y значения для нахождения порога
        List<Double> allY = new ArrayList<>();
        for (double[][] data : dataList) {
            for (double[] point : data) {
                if (Double.isFinite(point[0]) && Double.isFinite(point[1])
                        && Math.abs(point[1]) < 1e10) {
                    allY.add(Math.abs(point[1]));
                }
            }
        }

        // Находим 98-й перцентиль — отсекаем 2% самых больших значений
        double yThreshold;
        if (allY.isEmpty()) {
            yThreshold = 100;
        } else {
            Collections.sort(allY);
            int index = (int)(allY.size() * 0.98);
            if (index >= allY.size()) index = allY.size() - 1;
            if (index < 0) index = 0;
            yThreshold = allY.get(index) * 1.2;
        }

        // Теперь находим границы, игнорируя выбросы
        for (double[][] data : dataList) {
            for (double[] point : data) {
                if (Double.isFinite(point[0]) && Double.isFinite(point[1])
                        && Math.abs(point[1]) <= yThreshold) {
                    xMin = Math.min(xMin, point[0]);
                    xMax = Math.max(xMax, point[0]);
                    yMin = Math.min(yMin, point[1]);
                    yMax = Math.max(yMax, point[1]);
                }
            }
        }
        // =======================================

        if (xMin == Double.MAX_VALUE) {
            xMin = 0; xMax = 1; yMin = 0; yMax = 1;
        }

        double xRange = xMax - xMin;
        double yRange = yMax - yMin;
        if (xRange == 0) xRange = 1;
        if (yRange == 0) yRange = 1;

        xMin -= xRange * 0.05;
        xMax += xRange * 0.05;
        yMin -= yRange * 0.1;
        yMax += yRange * 0.1;
        xRange = xMax - xMin;
        yRange = yMax - yMin;

        // Формат чисел
        DecimalFormat dfX = getFormat(xRange);
        DecimalFormat dfY = getFormat(yRange);

        // Фон
        g2.setColor(new Color(250, 250, 255));
        g2.fillRect(margin, margin, graphWidth, graphHeight);
        g2.setColor(new Color(200, 200, 200));
        g2.drawRect(margin, margin, graphWidth, graphHeight);

        // Сетка
        int nTicksX = Math.min(10, graphWidth / 70);
        int nTicksY = Math.min(8, graphHeight / 50);

        g2.setColor(new Color(230, 230, 240));
        g2.setStroke(new BasicStroke(0.5f));
        for (int i = 0; i <= nTicksX; i++) {
            int x = margin + i * graphWidth / nTicksX;
            g2.drawLine(x, margin, x, margin + graphHeight);
        }
        for (int i = 0; i <= nTicksY; i++) {
            int y = margin + i * graphHeight / nTicksY;
            g2.drawLine(margin, y, margin + graphWidth, y);
        }

        // Оси
        g2.setColor(Color.DARK_GRAY);
        g2.setStroke(new BasicStroke(1.5f));

        int xAxisY = margin + graphHeight;
        int yAxisX = margin;

        if (yMin < 0 && yMax > 0) {
            xAxisY = margin + (int)(yMax / yRange * graphHeight);
        }
        if (xMin < 0 && xMax > 0) {
            yAxisX = margin + (int)(-xMin / xRange * graphWidth);
        }

        g2.drawLine(yAxisX, margin, yAxisX, margin + graphHeight);
        g2.drawLine(margin, xAxisY, margin + graphWidth, xAxisY);

        // Метки осей
        g2.setColor(Color.BLACK);
        g2.setFont(new Font("Segoe UI", Font.BOLD, 13));
        FontMetrics fmB = g2.getFontMetrics();

        g2.drawString(title, (width - fmB.stringWidth(title)) / 2, 25);
        g2.drawString(xLabel, margin + (graphWidth - fmB.stringWidth(xLabel)) / 2, height - 10);

        AffineTransform old = g2.getTransform();
        g2.rotate(-Math.PI/2);
        g2.drawString(yLabel, -(margin + (graphHeight + fmB.stringWidth(yLabel))/2), 20);
        g2.setTransform(old);

        // Числа на осях
        g2.setFont(new Font("Segoe UI", Font.PLAIN, 10));
        FontMetrics fm = g2.getFontMetrics();

        for (int i = 0; i <= nTicksX; i++) {
            double val = xMin + (double)i / nTicksX * xRange;
            int x = margin + i * graphWidth / nTicksX;
            String s = dfX.format(val);
            g2.drawString(s, x - fm.stringWidth(s)/2, xAxisY + 18);
        }

        for (int i = 0; i <= nTicksY; i++) {
            double val = yMax - (double)i / nTicksY * yRange;
            int y = margin + i * graphHeight / nTicksY;
            String s = dfY.format(val);
            g2.drawString(s, yAxisX - fm.stringWidth(s) - 8, y + 5);
        }

        // Кривые — рисуем только точки в пределах порога
        for (int d = 0; d < dataList.size(); d++) {
            double[][] data = dataList.get(d);
            Color color = curveColors[d % curveColors.length];

            g2.setColor(color);
            g2.setStroke(new BasicStroke(2f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));

            Path2D path = new Path2D.Double();
            boolean first = true;
            int count = 0;

            for (double[] point : data) {
                if (Double.isFinite(point[0]) && Double.isFinite(point[1])
                        && Math.abs(point[1]) <= yThreshold) {

                    double x = margin + (point[0] - xMin) / xRange * graphWidth;
                    double y = margin + (yMax - point[1]) / yRange * graphHeight;

                    // Только точки в видимой области
                    if (x >= margin - 50 && x <= margin + graphWidth + 50
                            && y >= margin - 50 && y <= margin + graphHeight + 50) {

                        if (first) {
                            path.moveTo(x, y);
                            first = false;
                        } else {
                            path.lineTo(x, y);
                        }
                        count++;
                    }
                }
            }

            if (count > 1) {
                g2.draw(path);
            }
        }

        // Легенда
        if (legendLabels != null) {
            int lx = margin + 10;
            int ly = margin + 10;
            int lw = 160;
            int lh = 28 * legendLabels.length + 10;

            g2.setColor(new Color(255, 255, 255, 220));
            g2.fillRoundRect(lx, ly, lw, lh, 8, 8);
            g2.setColor(Color.LIGHT_GRAY);
            g2.setStroke(new BasicStroke(1f));
            g2.drawRoundRect(lx, ly, lw, lh, 8, 8);

            for (int i = 0; i < legendLabels.length; i++) {
                int y = ly + 20 + i * 28;
                g2.setColor(curveColors[i % curveColors.length]);
                g2.setStroke(new BasicStroke(3f));
                g2.drawLine(lx + 8, y, lx + 35, y);
                g2.setColor(Color.BLACK);
                g2.setFont(new Font("Segoe UI", Font.PLAIN, 12));
                g2.drawString(legendLabels[i], lx + 42, y + 5);
            }
        }
    }

    private DecimalFormat getFormat(double range) {
        if (range < 0.001) return new DecimalFormat("0.0000");
        if (range < 0.01) return new DecimalFormat("0.000");
        if (range < 0.1) return new DecimalFormat("0.00");
        if (range < 10) return new DecimalFormat("0.0");
        if (range < 1000) return new DecimalFormat("0");
        return new DecimalFormat("0.0E0");
    }
}