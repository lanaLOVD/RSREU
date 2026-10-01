import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.border.TitledBorder;
import javax.swing.plaf.nimbus.NimbusLookAndFeel;
import java.awt.*;

public class Main extends JFrame {

    public Main() {
        setTitle("Лабораторная работа №5 — Решение ОДУ методом Рунге-Кутты | Вариант 6");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(1400, 900);
        setLocationRelativeTo(null);

        // Устанавливаем современный вид
        try {
            UIManager.setLookAndFeel(new NimbusLookAndFeel());
        } catch (Exception e) {
            try {
                UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }

        // Настраиваем стили
        customizeUI();

        // Создаем табулированную панель с иконками
        JTabbedPane tabbedPane = new JTabbedPane();
        tabbedPane.setFont(new Font("Segoe UI", Font.PLAIN, 14));

        tabbedPane.addTab("📐 Задание 1", new Task1Panel());
        tabbedPane.addTab("📊 Задание 2", new Task2Panel());
        tabbedPane.addTab("📈 Задание 3", new Task3Panel());

        add(tabbedPane);
    }

    private void customizeUI() {
        UIManager.put("TabbedPane.selected", new Color(70, 130, 180));
        UIManager.put("TabbedPane.background", new Color(240, 240, 245));
        UIManager.put("Panel.background", new Color(248, 248, 252));
        UIManager.put("Button.background", new Color(70, 130, 180));
        UIManager.put("Button.foreground", Color.WHITE);
        UIManager.put("Button.font", new Font("Segoe UI", Font.BOLD, 13));
        UIManager.put("Label.font", new Font("Segoe UI", Font.PLAIN, 13));
        UIManager.put("TextField.font", new Font("Segoe UI", Font.PLAIN, 13));
        UIManager.put("TitledBorder.font", new Font("Segoe UI", Font.BOLD, 13));
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Main().setVisible(true));
    }
}