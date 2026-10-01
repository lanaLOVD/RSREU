import javax.swing.*;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

public class HSLAdjuster extends JFrame {

    private BufferedImage originalImage;
    private BufferedImage editedImage;

    private JLabel imageLabel;
    private JSlider hueSlider, saturationSlider, lightnessSlider;
    private JComboBox<String> gammaCombo;
    private JButton loadButton, saveButton, resetButton;
    private JLabel hueValue, saturationValue, lightnessValue;

    private int hueShift = 0;
    private int saturationSliderVal = 100;
    private int lightnessSliderVal = 50;
    private double gamma = 1.0;

    public HSLAdjuster() {
        setTitle("HSL Adjuster (Вариант 17 - Степенной закон насыщенности)");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        initUI();
        setSize(1000, 700);
        setLocationRelativeTo(null);
        setVisible(true);
    }

    private void initUI() {
        // Панель инструментов
        JPanel topPanel = new JPanel();
        loadButton = new JButton("Загрузить изображение");
        saveButton = new JButton("Сохранить как...");
        resetButton = new JButton("Сбросить");
        topPanel.add(loadButton);
        topPanel.add(saveButton);
        topPanel.add(resetButton);
        add(topPanel, BorderLayout.NORTH);

        // Изображение
        imageLabel = new JLabel("Изображение не загружено", SwingConstants.CENTER);
        JScrollPane scrollPane = new JScrollPane(imageLabel);
        scrollPane.setPreferredSize(new Dimension(700, 600));
        add(scrollPane, BorderLayout.CENTER);

        // Панель управления
        JPanel controlPanel = new JPanel();
        controlPanel.setLayout(new BoxLayout(controlPanel, BoxLayout.Y_AXIS));
        controlPanel.setBorder(BorderFactory.createTitledBorder("Параметры HSL"));

        // --- Hue ---
        JPanel huePanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        huePanel.add(new JLabel("Hue (сдвиг):"));
        hueSlider = new JSlider(-100, 100, 0);
        hueSlider.setMajorTickSpacing(50);
        hueSlider.setPaintTicks(true);
        hueValue = new JLabel("0");
        huePanel.add(hueSlider);
        huePanel.add(hueValue);
        controlPanel.add(huePanel);

        // --- Saturation ---
        JPanel satPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        satPanel.add(new JLabel("Saturation:"));
        saturationSlider = new JSlider(0, 100, 100);
        saturationSlider.setMajorTickSpacing(25);
        saturationSlider.setPaintTicks(true);
        saturationValue = new JLabel("100%");
        satPanel.add(saturationSlider);
        satPanel.add(saturationValue);
        controlPanel.add(satPanel);

        // --- Lightness ---
        JPanel lightPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        lightPanel.add(new JLabel("Lightness:"));
        lightnessSlider = new JSlider(0, 100, 50);
        lightnessSlider.setMajorTickSpacing(25);
        lightnessSlider.setPaintTicks(true);
        lightnessValue = new JLabel("50%");
        lightPanel.add(lightnessSlider);
        lightPanel.add(lightnessValue);
        controlPanel.add(lightPanel);

        // --- Gamma ---
        JPanel gammaPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        gammaPanel.add(new JLabel("Gamma (S):"));
        gammaCombo = new JComboBox<>(new String[]{"0.5", "1.0", "2.0"});
        gammaCombo.setSelectedItem("1.0");
        gammaPanel.add(gammaCombo);
        controlPanel.add(gammaPanel);

        add(controlPanel, BorderLayout.EAST);

        // Обработчики
        loadButton.addActionListener(e -> loadImage());
        saveButton.addActionListener(e -> saveImage());
        resetButton.addActionListener(e -> resetSliders());

        ChangeListener sliderListener = e -> {
            updateValuesFromSliders();
            applyTransform();
        };

        hueSlider.addChangeListener(sliderListener);
        saturationSlider.addChangeListener(sliderListener);
        lightnessSlider.addChangeListener(sliderListener);

        gammaCombo.addActionListener(e -> {
            String selected = (String) gammaCombo.getSelectedItem();
            if (selected != null) {
                gamma = Double.parseDouble(selected);
                applyTransform();
            }
        });
    }

    private void loadImage() {
        JFileChooser fc = new JFileChooser();
        if (fc.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
            try {
                File file = fc.getSelectedFile();
                BufferedImage loaded = ImageIO.read(file);
                if (loaded == null) {
                    JOptionPane.showMessageDialog(this, "Не удалось прочитать файл!");
                    return;
                }

                // Конвертируем в RGB
                originalImage = new BufferedImage(loaded.getWidth(), loaded.getHeight(), BufferedImage.TYPE_INT_RGB);
                Graphics2D g = originalImage.createGraphics();
                g.drawImage(loaded, 0, 0, null);
                g.dispose();

                editedImage = new BufferedImage(originalImage.getWidth(), originalImage.getHeight(), BufferedImage.TYPE_INT_RGB);
                Graphics2D g2 = editedImage.createGraphics();
                g2.drawImage(originalImage, 0, 0, null);
                g2.dispose();

                imageLabel.setText("");
                imageLabel.setIcon(new ImageIcon(editedImage));

                resetSliders();
            } catch (IOException ex) {
                JOptionPane.showMessageDialog(this, "Ошибка загрузки: " + ex.getMessage());
            }
        }
    }

    private void saveImage() {
        if (editedImage == null) {
            JOptionPane.showMessageDialog(this, "Нет изображения!");
            return;
        }
        JFileChooser fc = new JFileChooser();
        if (fc.showSaveDialog(this) == JFileChooser.APPROVE_OPTION) {
            try {
                File file = fc.getSelectedFile();
                String name = file.getName().toLowerCase();
                if (!name.endsWith(".png") && !name.endsWith(".jpg") && !name.endsWith(".bmp")) {
                    file = new File(file.getAbsolutePath() + ".png");
                }
                ImageIO.write(editedImage, "png", file);
                JOptionPane.showMessageDialog(this, "Сохранено!");
            } catch (IOException ex) {
                JOptionPane.showMessageDialog(this, "Ошибка сохранения: " + ex.getMessage());
            }
        }
    }

    private void resetSliders() {
        if (originalImage == null) return;

        hueSlider.setValue(0);
        saturationSlider.setValue(100);
        lightnessSlider.setValue(50);
        gammaCombo.setSelectedItem("1.0");

        Graphics2D g = editedImage.createGraphics();
        g.drawImage(originalImage, 0, 0, null);
        g.dispose();

        imageLabel.setIcon(new ImageIcon(editedImage));
    }

    private void updateValuesFromSliders() {
        hueShift = hueSlider.getValue();
        saturationSliderVal = saturationSlider.getValue();
        lightnessSliderVal = lightnessSlider.getValue();

        hueValue.setText(String.valueOf(hueShift));
        saturationValue.setText(saturationSliderVal + "%");
        lightnessValue.setText(lightnessSliderVal + "%");
    }

    private void applyTransform() {
        if (originalImage == null || editedImage == null) return;

        int width = originalImage.getWidth();
        int height = originalImage.getHeight();

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int rgb = originalImage.getRGB(x, y);
                float r = ((rgb >> 16) & 0xFF) / 255f;
                float g = ((rgb >> 8) & 0xFF) / 255f;
                float b = (rgb & 0xFF) / 255f;

                float[] hsl = rgbToHsl(r, g, b);
                float H_orig = hsl[0];
                float S_orig = hsl[1];
                float L_orig = hsl[2];

                // Сдвиг Hue
                float H_new = (H_orig * 360f + hueShift * 1.8f) % 360f;
                if (H_new < 0) H_new += 360f;
                H_new /= 360f;

                // Масштабирование Saturation
                float sMultiplier = (float) Math.pow(saturationSliderVal / 100f, gamma);
                float S_new = S_orig * sMultiplier;
                S_new = Math.max(0f, Math.min(1f, S_new));

                // Масштабирование Lightness
                float lMultiplier = lightnessSliderVal / 50f;
                float L_new = L_orig * lMultiplier;
                L_new = Math.max(0f, Math.min(1f, L_new));

                float[] newRgb = hslToRgb(H_new, S_new, L_new);
                int newR = Math.max(0, Math.min(255, Math.round(newRgb[0] * 255)));
                int newG = Math.max(0, Math.min(255, Math.round(newRgb[1] * 255)));
                int newB = Math.max(0, Math.min(255, Math.round(newRgb[2] * 255)));

                editedImage.setRGB(x, y, (newR << 16) | (newG << 8) | newB);
            }
        }
        imageLabel.setIcon(new ImageIcon(editedImage));
    }

    // ====== Методы конвертации ======

    public static float[] rgbToHsl(float r, float g, float b) {
        float max = Math.max(r, Math.max(g, b));
        float min = Math.min(r, Math.min(g, b));
        float L = (max + min) / 2f;

        float H = 0, S = 0;
        float delta = max - min;

        if (delta == 0) {
            return new float[]{H, S, L};
        }

        if (L <= 0.5f) {
            S = delta / (max + min);
        } else {
            S = delta / (2f - max - min);
        }

        if (max == r) {
            H = ((g - b) / delta) + (g < b ? 6f : 0f);
        } else if (max == g) {
            H = ((b - r) / delta) + 2f;
        } else {
            H = ((r - g) / delta) + 4f;
        }
        H /= 6f;

        H = Math.max(0f, Math.min(1f, H));
        S = Math.max(0f, Math.min(1f, S));
        L = Math.max(0f, Math.min(1f, L));

        return new float[]{H, S, L};
    }

    public static float[] hslToRgb(float h, float s, float l) {
        if (s == 0) {
            return new float[]{l, l, l};
        }

        float q = l < 0.5f ? l * (1 + s) : l + s - l * s;
        float p = 2 * l - q;

        float r = hueToRgb(p, q, h + 1f / 3f);
        float g = hueToRgb(p, q, h);
        float b = hueToRgb(p, q, h - 1f / 3f);

        return new float[]{
                Math.max(0f, Math.min(1f, r)),
                Math.max(0f, Math.min(1f, g)),
                Math.max(0f, Math.min(1f, b))
        };
    }

    private static float hueToRgb(float p, float q, float t) {
        if (t < 0) t += 1;
        if (t > 1) t -= 1;
        if (t < 1f / 6f) return p + (q - p) * 6f * t;
        if (t < 1f / 2f) return q;
        if (t < 2f / 3f) return p + (q - p) * (2f / 3f - t) * 6f;
        return p;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new HSLAdjuster());
    }
}