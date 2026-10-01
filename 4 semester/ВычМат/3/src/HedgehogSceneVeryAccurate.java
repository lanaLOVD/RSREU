import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;

public class HedgehogSceneVeryAccurate extends JPanel {

    public static void main(String[] args) {
        JFrame frame = new JFrame("Ёжики на поляне");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.add(new HedgehogSceneVeryAccurate());
        frame.setSize(820, 620);           // близко к пропорциям оригинала
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2 = (Graphics2D) g;
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        // Небо
        g2.setColor(new Color(88, 194, 255));
        g2.fillRect(0, 0, 820, 355);

        // Солнце
        g2.setColor(new Color(255, 204, 0));
        g2.fillOval(635, 48, 135, 135);

        // Лучи солнца
        g2.setColor(new Color(255, 235, 90));
        g2.setStroke(new BasicStroke(9f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
        for (int i = 0; i < 12; i++) {
            double ang = i * Math.PI / 6 + 0.2;
            int x1 = 700 + (int)(82 * Math.cos(ang));
            int y1 = 115 + (int)(82 * Math.sin(ang));
            int x2 = 700 + (int)(125 * Math.cos(ang));
            int y2 = 115 + (int)(125 * Math.sin(ang));
            g2.drawLine(x1, y1, x2, y2);
        }

        // Облака
        drawCloud(g2, 95, 68);
        drawCloud(g2, 355, 48);
        drawCloud(g2, 545, 105);

        // Земля
        g2.setColor(new Color(34, 155, 48));
        g2.fillRect(0, 355, 820, 265);

        // Холм
        g2.setColor(new Color(46, 175, 58));
        Path2D hill = new Path2D.Double();
        hill.moveTo(-20, 380);
        hill.curveTo(120, 310, 380, 285, 820, 375);
        hill.lineTo(820, 620);
        hill.lineTo(-20, 620);
        hill.closePath();
        g2.fill(hill);

        // Деревья
        drawTree(g2, 82, 255);   // левое большое
        drawTree(g2, 295, 228);  // среднее
        drawTree(g2, 695, 248);  // правое

        // Грибы
        drawMushroom(g2, 195, 345, 1.05);   // левый верхний
        drawMushroom(g2, 385, 385, 0.78);
        drawMushroom(g2, 465, 345, 0.92);
        drawMushroom(g2, 555, 405, 0.85);
        drawMushroom(g2, 715, 425, 0.88);
        drawMushroom(g2, 265, 275, 0.62);   // маленький сверху

        // Ёжики
        drawHedgehog(g2, 125, 375);   // верхний левый
        drawHedgehog(g2, 345, 455);   // нижний центр
        drawHedgehog(g2, 525, 445);   // нижний правый

        // Кустики травы
        drawGrass(g2, 35, 415, 1.1);
        drawGrass(g2, 205, 435, 0.9);
        drawGrass(g2, 410, 440, 1.0);
        drawGrass(g2, 615, 455, 1.05);
        drawGrass(g2, 665, 390, 0.8);
    }

    private void drawCloud(Graphics2D g, int x, int y) {
        g.setColor(Color.WHITE);
        g.fillOval(x,     y,     68, 42);
        g.fillOval(x+22,  y-15,  55, 48);
        g.fillOval(x+48,  y-5,   52, 40);
        g.fillOval(x+70,  y+5,   38, 35);
    }

    private void drawTree(Graphics2D g, int x, int y) {
        // Ствол
        g.setColor(new Color(125, 68, 22));
        g.fillRoundRect(x-11, y+25, 23, 105, 12, 12);

        // Крона
        g.setColor(new Color(28, 148, 45));
        g.fillOval(x-48, y-48, 98, 75);
        g.fillOval(x-39, y-72, 80, 68);
        g.fillOval(x-28, y-88, 58, 52);
    }

    private void drawMushroom(Graphics2D g, int x, int y, double scale) {
        // Ножка
        g.setColor(new Color(252, 240, 215));
        g.fillOval(x - (int)(10*scale), y + (int)(14*scale), (int)(20*scale), (int)(36*scale));

        // Шляпка
        g.setColor(new Color(198, 68, 48));
        g.fillOval(x - (int)(24*scale), y - (int)(6*scale), (int)(48*scale), (int)(27*scale));

        // Блик на шляпке
        g.setColor(new Color(255, 155, 120));
        g.fillOval(x - (int)(16*scale), y - (int)(3*scale), (int)(16*scale), (int)(12*scale));
    }

    private void drawHedgehog(Graphics2D g, int x, int y) {
        // Тело
        g.setColor(new Color(245, 245, 245));
        g.fillOval(x-29, y-17, 55, 31);

        // Мордочка
        g.fillOval(x-37, y-16, 23, 21);

        // Нос
        g.setColor(Color.BLACK);
        g.fillOval(x-40, y-9, 8, 7);

        // Глаз
        g.fillOval(x-24, y-13, 6, 6);
        g.setColor(Color.WHITE);
        g.fillOval(x-23, y-15, 2, 2);

        // Иглы (более точная форма как на оригинале)
        g.setColor(new Color(30, 30, 35));
        g.setStroke(new BasicStroke(2.8f));
        for (int i = 0; i < 18; i++) {
            double ang = -1.25 + i * 0.145;
            int len = 24 + (i % 3);
            int dx = (int)(len * Math.cos(ang));
            int dy = (int)(len * 0.75 * Math.sin(ang)) - 7;
            g.drawLine(x-7, y-9, x-7 + dx, y-9 + dy);
        }
    }

    private void drawGrass(Graphics2D g, int x, int y, double scale) {
        g.setColor(new Color(40, 170, 55));
        g.setStroke(new BasicStroke(3.5f));
        for (int i = -4; i <= 4; i++) {
            int offset = i * 7;
            int length = (int)((28 + Math.abs(i)*4) * scale);
            g.drawLine(x + offset, y, x + offset - 6, y - length);
            g.drawLine(x + offset, y, x + offset + 5, y - length + 8);
        }
    }
}