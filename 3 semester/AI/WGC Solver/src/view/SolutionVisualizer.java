package view;

import model.RiverSituation;
import model.Passenger;
import javax.swing.*;
import javax.swing.border.TitledBorder;
import javax.swing.border.LineBorder;
import java.awt.*;
import java.util.List;
import java.util.Set;

/**
 * Универсальный визуализатор решений для всех алгоритмов поиска.
 * Отображает пошаговую анимацию переправы через реку.
 */
public class SolutionVisualizer extends JFrame {

    private final List<RiverSituation> solution;
    private final String algorithmName;
    private int currentStep = 0;
    private Timer autoPlayTimer;

    private JLabel stepLabel;
    private JPanel leftBankPanel;
    private JPanel rightBankPanel;
    private JLabel boatLabel;
    private JLabel algorithmLabel;
    private JLabel statsLabel;

    public SolutionVisualizer(List<RiverSituation> solution, String algorithmName, long executionTime, int visitedStates) {
        this.solution = solution;
        this.algorithmName = algorithmName;

        setTitle("🎯 Решение задачи о переправе — " + algorithmName);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setSize(1100, 650);
        setLocationRelativeTo(null);
        setLayout(new BorderLayout());
        getContentPane().setBackground(new Color(240, 248, 255));

        // Верхняя панель с информацией
        JPanel topPanel = createTopPanel(executionTime, visitedStates);
        add(topPanel, BorderLayout.NORTH);

        // Основная панель с берегами и рекой
        JPanel mainPanel = createMainPanel();
        add(mainPanel, BorderLayout.CENTER);

        // Нижняя панель с кнопками управления
        JPanel controlPanel = createControlPanel();
        add(controlPanel, BorderLayout.SOUTH);

        // Показываем первый шаг
        showStep(0);

        setVisible(true);
    }

    private JPanel createTopPanel(long executionTime, int visitedStates) {
        JPanel panel = new JPanel(new GridLayout(3, 1, 5, 5));
        panel.setBackground(new Color(130,137,143));
        panel.setBorder(BorderFactory.createEmptyBorder(10, 15, 10, 15));

        // Название алгоритма
        algorithmLabel = new JLabel("📊 Алгоритм: " + algorithmName, SwingConstants.CENTER);
        algorithmLabel.setFont(new Font("Segoe UI", Font.BOLD, 16));
        algorithmLabel.setForeground(Color.WHITE);

        // Статистика
        statsLabel = new JLabel(String.format("⏱ Время: %d мс | 📍 Посещено состояний: %d | 📏 Длина решения: %d шагов",
                executionTime, visitedStates, solution.size() - 1), SwingConstants.CENTER);
        statsLabel.setFont(new Font("Segoe UI", Font.PLAIN, 14));
        statsLabel.setForeground(Color.WHITE);

        // Текущий шаг
        stepLabel = new JLabel("", SwingConstants.CENTER);
        stepLabel.setFont(new Font("Segoe UI", Font.BOLD, 18));
        stepLabel.setForeground(new Color(247,242,26));

        panel.add(algorithmLabel);
        panel.add(statsLabel);
        panel.add(stepLabel);

        return panel;
    }

    private JPanel createMainPanel() {
        JPanel mainPanel = new JPanel(new BorderLayout(20, 0));
        mainPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));
        mainPanel.setBackground(new Color(213,213,213));

        // Левый берег
        leftBankPanel = createBankPanel("🌿 ЛЕВЫЙ БЕРЕГ", new Color(168, 228, 182));
        mainPanel.add(leftBankPanel, BorderLayout.WEST);

        // Река с лодкой
        JPanel riverPanel = createRiverPanel();
        mainPanel.add(riverPanel, BorderLayout.CENTER);

        // Правый берег
        rightBankPanel = createBankPanel("🏡 ПРАВЫЙ БЕРЕГ", new Color(255,189,136));
        mainPanel.add(rightBankPanel, BorderLayout.EAST);

        return mainPanel;
    }

    private JPanel createBankPanel(String title, Color color) {
        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        panel.setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createTitledBorder(
                        BorderFactory.createLineBorder(Color.DARK_GRAY, 2),
                        title,
                        TitledBorder.CENTER,
                        TitledBorder.TOP,
                        new Font("Segoe UI", Font.BOLD, 16)
                ),
                BorderFactory.createEmptyBorder(10, 10, 10, 10)
        ));
        panel.setBackground(color);
        panel.setPreferredSize(new Dimension(280, 450));
        return panel;
    }

    private JPanel createRiverPanel() {
        JPanel riverPanel = new JPanel(new BorderLayout());
        riverPanel.setBackground(new Color(127,199,255));
        riverPanel.setPreferredSize(new Dimension(300, 450));

        // Лодка
        boatLabel = new JLabel("⛵", SwingConstants.CENTER);
        boatLabel.setFont(new Font("Segoe UI", Font.PLAIN, 90));
        boatLabel.setForeground(new Color(255,79,0));
        riverPanel.add(boatLabel, BorderLayout.CENTER);

        // Анимация воды
        JLabel waterLabel = new JLabel("~~~~~~~~~~~~~~~~~~~ Р Е К А ~~~~~~~~~~~~~~~~~~~", SwingConstants.CENTER);
        waterLabel.setFont(new Font("Monospaced", Font.BOLD, 14));
        waterLabel.setForeground(Color.WHITE);
        riverPanel.add(waterLabel, BorderLayout.SOUTH);

        return riverPanel;
    }

    private JPanel createControlPanel() {
        JPanel panel = new JPanel();
        panel.setBackground(new Color(245, 245, 245));
        panel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        // Стилизованные кнопки
        JButton prevBtn = createStyledButton("◀◀ ПРЕДЫДУЩИЙ", new Color(70, 130, 200));
        JButton nextBtn = createStyledButton("СЛЕДУЮЩИЙ ▶▶", new Color(70, 130, 200));
        JButton autoBtn = createStyledButton("▶ АВТОПРОИГРЫВАНИЕ", new Color(60, 179, 113));
        JButton closeBtn = createStyledButton("✖ ЗАКРЫТЬ", new Color(220, 20, 60));

        prevBtn.addActionListener(e -> showStep(Math.max(0, currentStep - 1)));
        nextBtn.addActionListener(e -> showStep(Math.min(solution.size() - 1, currentStep + 1)));
        autoBtn.addActionListener(e -> toggleAutoPlay(autoBtn));
        closeBtn.addActionListener(e -> dispose());

        panel.add(prevBtn);
        panel.add(nextBtn);
        panel.add(autoBtn);
        panel.add(closeBtn);

        return panel;
    }

    private JButton createStyledButton(String text, Color bgColor) {
        JButton button = new JButton(text);
        button.setFont(new Font("Segoe UI", Font.BOLD, 14));
        button.setBackground(bgColor);
        button.setForeground(new Color(71,74,81));
        button.setFocusPainted(false);
        button.setBorder(BorderFactory.createEmptyBorder(10, 20, 10, 20));
        button.setCursor(new Cursor(Cursor.HAND_CURSOR));

        // Эффект наведения
        button.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseEntered(java.awt.event.MouseEvent evt) {
                button.setBackground(bgColor.darker());
            }
            public void mouseExited(java.awt.event.MouseEvent evt) {
                button.setBackground(bgColor);
            }
        });

        return button;
    }

    private void showStep(int step) {
        currentStep = step;
        RiverSituation situation = solution.get(step);

        // Обновляем информацию о шаге
        String statusIcon = situation.isSafe() ? "✅" : "❌";
        String statusText = situation.isSafe() ? "Безопасно" : "ОПАСНО!";
        String goalText = situation.isGoal() ? " 🎉 ЦЕЛЬ ДОСТИГНУТА! 🎉" : "";

        stepLabel.setText(String.format("📌 Шаг %d из %d | %s %s%s",
                step, solution.size() - 1, statusIcon, statusText, goalText));

        // Обновляем берега
        updateBank(leftBankPanel, situation.getLeftBank());
        updateBank(rightBankPanel, situation.getRightBank());

        // Анимируем лодку
        if (situation.isBoatOnLeft()) {
            boatLabel.setText("⛵  ←");
            boatLabel.setHorizontalAlignment(SwingConstants.LEFT);
        } else {
            boatLabel.setText("→  ⛵");
            boatLabel.setHorizontalAlignment(SwingConstants.RIGHT);
        }

        // Подсветка текущего шага в консоли
        System.out.println("  ▶ Показан шаг " + step + " из " + (solution.size() - 1));
    }

    private void updateBank(JPanel panel, Set<Passenger> passengers) {
        panel.removeAll();

        if (passengers.isEmpty()) {
            JLabel emptyLabel = new JLabel("✨ ПУСТО ✨", SwingConstants.CENTER);
            emptyLabel.setFont(new Font("Segoe UI", Font.ITALIC, 18));
            emptyLabel.setForeground(new Color(71,74,81));
            emptyLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
            panel.add(emptyLabel);
        } else {
            for (Passenger p : passengers) {
                JPanel passengerPanel = createPassengerPanel(p);
                passengerPanel.setAlignmentX(Component.CENTER_ALIGNMENT);
                panel.add(passengerPanel);
                panel.add(Box.createRigidArea(new Dimension(0, 5)));
            }
        }

        panel.revalidate();
        panel.repaint();
    }

    private JPanel createPassengerPanel(Passenger passenger) {
        JPanel panel = new JPanel();
        panel.setLayout(new BorderLayout());
        panel.setBackground(new Color(255, 255, 255, 200));
        panel.setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createLineBorder(Color.GRAY, 1),
                BorderFactory.createEmptyBorder(8, 12, 8, 12)
        ));
        panel.setMaximumSize(new Dimension(260, 60));

        String emoji = getEmoji(passenger);
        JLabel emojiLabel = new JLabel(emoji, SwingConstants.CENTER);
        emojiLabel.setFont(new Font("Segoe UI", Font.PLAIN, 32));

        JLabel nameLabel = new JLabel(passenger.getName(), SwingConstants.CENTER);
        nameLabel.setFont(new Font("Segoe UI", Font.BOLD, 14));

        panel.add(emojiLabel, BorderLayout.WEST);
        panel.add(nameLabel, BorderLayout.CENTER);

        return panel;
    }

    private String getEmoji(Passenger p) {
        switch (p.getName()) {
            case "Фермер": return "👨‍🌾";
            case "Волк": return "🐺";
            case "Лиса": return "🦊";
            case "Коза": return "🐐";
            case "Курица": return "🐔";
            case "Капуста": return "🥬";
            case "Зерно": return "🌾";
            default: return "📦";
        }
    }

    private void toggleAutoPlay(JButton btn) {
        if (autoPlayTimer != null && autoPlayTimer.isRunning()) {
            autoPlayTimer.stop();
            btn.setText("▶ АВТОПРОИГРЫВАНИЕ");
            btn.setBackground(new Color(60, 179, 113));
        } else {
            autoPlayTimer = new Timer(1500, e -> {
                if (currentStep < solution.size() - 1) {
                    showStep(currentStep + 1);
                } else {
                    autoPlayTimer.stop();
                    btn.setText("▶ АВТОПРОИГРЫВАНИЕ");
                    btn.setBackground(new Color(60, 179, 113));
                    JOptionPane.showMessageDialog(this,
                            "🎉 Поздравляем! Решение полностью продемонстрировано! 🎉",
                            "Завершение демонстрации",
                            JOptionPane.INFORMATION_MESSAGE);
                }
            });
            autoPlayTimer.start();
            btn.setText("⏸ ПАУЗА");
            btn.setBackground(new Color(255, 140, 0));
        }
    }
}