import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.geometry.*;
import javafx.scene.*;
import javafx.scene.canvas.*;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.*;
import javafx.scene.paint.*;
import javafx.scene.shape.*;
import javafx.scene.text.*;
import javafx.stage.Stage;
import javafx.util.Callback;

import java.util.*;

/**
 * Практическая работа №6 — Вариант 17
 * Санкт-Петербург, Июнь («Белые ночи»)
 * Построение функций принадлежности на основе экспертных оценок
 * JavaFX GUI — графики МФ + таблицы экспертов
 */
public class FuzzyWeatherFX extends Application {

    // ─── Универсальные множества ───────────────────────────────────────────
    static final String[] TEMP_INT   = {"-5..0","0..5","5..10","10..15","15..20","20..25","25..30"};
    static final String[] PRECIP_INT = {"0..10","10..20","20..35","35..50","50..65","65..80","80..100"};
    static final String[] WIND_INT   = {"0..2","2..4","4..6","6..8","8..10","10..12","12..15"};
    static final String[] TERMS      = {"Низкий","Средний","Высокий"};
    static final String[] EXPERTS    = {"Метеоролог","Климатолог","Житель","Турист","Гидролог"};

    // ─── Экспертные оценки [эксперт][терм][интервал] ─────────────────────
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

    // ─── Цвета термов ─────────────────────────────────────────────────────
    static final Color[] TERM_FILL   = {Color.rgb(41,128,185,0.18), Color.rgb(39,174,96,0.18), Color.rgb(231,76,60,0.18)};
    static final Color[] TERM_STROKE = {Color.rgb(41,128,185), Color.rgb(39,174,96), Color.rgb(231,76,60)};

    // ─── Расчёт μ ─────────────────────────────────────────────────────────
    static double[][] calcMu(int[][][] data) {
        int K = data.length, T = data[0].length, N = data[0][0].length;
        double[][] mu = new double[T][N];
        for (int j = 0; j < T; j++)
            for (int i = 0; i < N; i++) {
                int s = 0;
                for (int k = 0; k < K; k++) s += data[k][j][i];
                mu[j][i] = (double) s / K;
            }
        return mu;
    }

    // ══════════════════════════════════════════════════════════════════════
    // Canvas-график функций принадлежности
    // ══════════════════════════════════════════════════════════════════════
    static Canvas buildChart(double[][] mu, String[] intervals, String varName, String unit) {
        int W = 500, H = 300;
        Canvas canvas = new Canvas(W, H);
        GraphicsContext g = canvas.getGraphicsContext2D();

        int padL = 52, padR = 20, padT = 36, padB = 52;
        int cW = W - padL - padR, cH = H - padT - padB;
        int N = intervals.length;
        double stepX = (double) cW / (N - 1);

        // Фон
        g.setFill(Color.rgb(248, 251, 255));
        g.fillRect(padL, padT, cW, cH);

        // Сетка
        g.setStroke(Color.rgb(210, 220, 235));
        g.setLineWidth(0.7);
        for (int yi = 0; yi <= 5; yi++) {
            double y = padT + cH - yi * cH / 5.0;
            g.strokeLine(padL, y, padL + cW, y);
        }
        for (int i = 0; i < N; i++) {
            double x = padL + i * stepX;
            g.strokeLine(x, padT, x, padT + cH);
        }

        // Оси
        g.setStroke(Color.rgb(60, 80, 110));
        g.setLineWidth(1.8);
        g.strokeLine(padL, padT, padL, padT + cH);
        g.strokeLine(padL, padT + cH, padL + cW, padT + cH);

        // Подписи Y
        g.setFont(Font.font("SansSerif", 10));
        g.setFill(Color.rgb(80, 90, 110));
        for (int yi = 0; yi <= 5; yi++) {
            double y = padT + cH - yi * cH / 5.0;
            String lbl = String.format("%.1f", yi / 5.0);
            g.fillText(lbl, padL - 34, y + 4);
        }

        // Подписи X
        g.setFont(Font.font("SansSerif", 9));
        for (int i = 0; i < N; i++) {
            double x = padL + i * stepX;
            g.fillText(intervals[i], x - 13, padT + cH + 14);
        }

        // Единица измерения
        g.setFont(Font.font("SansSerif", FontPosture.ITALIC, 10));
        g.setFill(Color.rgb(120, 130, 150));
        g.fillText(unit, padL + cW / 2.0 - 10, padT + cH + 30);

        // Кривые МФ (заливка + линия + точки)
        for (int j = 0; j < mu.length; j++) {
            double[] xs = new double[N], ys = new double[N];
            for (int i = 0; i < N; i++) {
                xs[i] = padL + i * stepX;
                ys[i] = padT + cH - mu[j][i] * cH;
            }

            // Заливка
            g.setFill(TERM_FILL[j]);
            g.beginPath();
            g.moveTo(xs[0], padT + cH);
            for (int i = 0; i < N; i++) g.lineTo(xs[i], ys[i]);
            g.lineTo(xs[N-1], padT + cH);
            g.closePath();
            g.fill();

            // Линия
            g.setStroke(TERM_STROKE[j]);
            g.setLineWidth(2.4);
            g.beginPath();
            g.moveTo(xs[0], ys[0]);
            for (int i = 1; i < N; i++) g.lineTo(xs[i], ys[i]);
            g.stroke();

            // Точки и подписи μ
            for (int i = 0; i < N; i++) {
                g.setFill(TERM_STROKE[j]);
                g.fillOval(xs[i] - 4.5, ys[i] - 4.5, 9, 9);
                if (mu[j][i] > 0.01) {
                    g.setFont(Font.font("SansSerif", FontWeight.BOLD, 8));
                    g.setFill(TERM_STROKE[j]);
                    g.fillText(String.format("%.1f", mu[j][i]), xs[i] - 7, ys[i] - 7);
                }
            }
        }

        // Легенда
        g.setFont(Font.font("SansSerif", FontWeight.BOLD, 10));
        double lx = padL + 8, ly = padT + 6;
        for (int j = 0; j < 3; j++) {
            g.setFill(TERM_STROKE[j]);
            g.fillRect(lx, ly + j * 17, 14, 10);
            g.setFill(Color.rgb(40, 50, 70));
            g.setFont(Font.font("SansSerif", 10));
            g.fillText(TERMS[j], lx + 18, ly + j * 17 + 9);
        }

        // Заголовок графика
        g.setFont(Font.font("SansSerif", FontWeight.BOLD, 13));
        g.setFill(Color.rgb(26, 58, 92));
        double tw = varName.length() * 7.5;
        g.fillText(varName, W / 2.0 - tw / 2, 18);

        // Рамка
        g.setStroke(Color.rgb(180, 195, 215));
        g.setLineWidth(1.0);
        g.strokeRect(padL, padT, cW, cH);

        return canvas;
    }

    // ══════════════════════════════════════════════════════════════════════
    // TableView для экспертных оценок (Таблица 1)
    // ══════════════════════════════════════════════════════════════════════
    static TableView<ObservableList<String>> buildExpertTableView(int[][][] data, String[] intervals) {
        TableView<ObservableList<String>> tv = new TableView<>();
        tv.setEditable(false);

        // Колонки
        TableColumn<ObservableList<String>, String> colExp = new TableColumn<>("Эксперт");
        colExp.setCellValueFactory(p -> new javafx.beans.property.SimpleStringProperty(p.getValue().get(0)));
        colExp.setPrefWidth(100); colExp.setStyle("-fx-alignment: CENTER-LEFT;");

        TableColumn<ObservableList<String>, String> colTerm = new TableColumn<>("Терм");
        colTerm.setCellValueFactory(p -> new javafx.beans.property.SimpleStringProperty(p.getValue().get(1)));
        colTerm.setPrefWidth(80); colTerm.setStyle("-fx-alignment: CENTER;");

        tv.getColumns().add(colExp);
        tv.getColumns().add(colTerm);

        for (int i = 0; i < intervals.length; i++) {
            final int idx = i + 2;
            TableColumn<ObservableList<String>, String> col = new TableColumn<>(intervals[i]);
            col.setCellValueFactory(p -> new javafx.beans.property.SimpleStringProperty(p.getValue().get(idx)));
            col.setPrefWidth(58);
            col.setStyle("-fx-alignment: CENTER;");
            // Раскраска ячеек: 1 = зелёный, 0 = серый
            col.setCellFactory(c -> new TableCell<ObservableList<String>, String>() {
                @Override protected void updateItem(String item, boolean empty) {
                    super.updateItem(item, empty);
                    if (empty || item == null) { setText(null); setStyle(""); return; }
                    setText(item);
                    setAlignment(Pos.CENTER);
                    if ("1".equals(item)) setStyle("-fx-background-color: #d4efdf; -fx-text-fill: #1a7a3a; -fx-font-weight:bold; -fx-alignment:center;");
                    else setStyle("-fx-background-color: #f5f5f5; -fx-text-fill: #aaaaaa; -fx-alignment:center;");
                }
            });
            tv.getColumns().add(col);
        }

        // Строки
        ObservableList<ObservableList<String>> rows = FXCollections.observableArrayList();
        for (int k = 0; k < data.length; k++) {
            for (int j = 0; j < 3; j++) {
                ObservableList<String> row = FXCollections.observableArrayList();
                row.add(j == 0 ? EXPERTS[k] : "");
                row.add(TERMS[j]);
                for (int i = 0; i < intervals.length; i++)
                    row.add(String.valueOf(data[k][j][i]));
                rows.add(row);
            }
        }
        tv.setItems(rows);
        tv.setPrefHeight(310);
        tv.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);
        return tv;
    }

    // ══════════════════════════════════════════════════════════════════════
    // TableView для μ (Таблица 2)
    // ══════════════════════════════════════════════════════════════════════
    static TableView<ObservableList<String>> buildMuTableView(double[][] mu, String[] intervals) {
        TableView<ObservableList<String>> tv = new TableView<>();
        tv.setEditable(false);

        TableColumn<ObservableList<String>, String> colTerm = new TableColumn<>("Терм");
        colTerm.setCellValueFactory(p -> new javafx.beans.property.SimpleStringProperty(p.getValue().get(0)));
        colTerm.setPrefWidth(80); colTerm.setStyle("-fx-alignment: CENTER;");

        TableColumn<ObservableList<String>, String> colRow = new TableColumn<>("Тип");
        colRow.setCellValueFactory(p -> new javafx.beans.property.SimpleStringProperty(p.getValue().get(1)));
        colRow.setPrefWidth(80); colRow.setStyle("-fx-alignment: CENTER;");

        tv.getColumns().add(colTerm);
        tv.getColumns().add(colRow);

        Color[] rowBg = {Color.rgb(41,128,185,0.15), Color.rgb(39,174,96,0.15), Color.rgb(231,76,60,0.15)};

        for (int i = 0; i < intervals.length; i++) {
            final int idx = i + 2;
            TableColumn<ObservableList<String>, String> col = new TableColumn<>(intervals[i]);
            col.setCellValueFactory(p -> new javafx.beans.property.SimpleStringProperty(p.getValue().get(idx)));
            col.setPrefWidth(65);
            col.setStyle("-fx-alignment: CENTER;");
            col.setCellFactory(c -> new TableCell<ObservableList<String>, String>() {
                @Override protected void updateItem(String item, boolean empty) {
                    super.updateItem(item, empty);
                    if (empty || item == null) { setText(null); setStyle(""); return; }
                    setText(item);
                    setAlignment(Pos.CENTER);
                    int r = getIndex();
                    boolean isMuRow = (r % 2 == 1);
                    int term = r / 2;
                    if (term >= 0 && term < 3 && isMuRow) {
                        Color bg = rowBg[term];
                        String hex = String.format("rgba(%d,%d,%d,0.3)",
                                (int)(bg.getRed()*255),(int)(bg.getGreen()*255),(int)(bg.getBlue()*255));
                        Color tc = TERM_STROKE[term];
                        String tcHex = String.format("#%02x%02x%02x",
                                (int)(tc.getRed()*255),(int)(tc.getGreen()*255),(int)(tc.getBlue()*255));
                        setStyle("-fx-background-color: derive(" + tcHex + ",80%); -fx-text-fill:" + tcHex + "; -fx-font-weight:bold; -fx-alignment:center;");
                    } else {
                        setStyle("-fx-background-color: #f7f9fc; -fx-alignment:center;");
                    }
                }
            });
            tv.getColumns().add(col);
        }

        ObservableList<ObservableList<String>> rows = FXCollections.observableArrayList();
        for (int j = 0; j < 3; j++) {
            // Строка голосов
            ObservableList<String> r1 = FXCollections.observableArrayList();
            r1.add(TERMS[j]); r1.add("Σ голосов");
            for (int i = 0; i < intervals.length; i++)
                r1.add(String.valueOf((int)Math.round(mu[j][i] * 5)));
            rows.add(r1);
            // Строка μ
            ObservableList<String> r2 = FXCollections.observableArrayList();
            r2.add(""); r2.add("μ(u)");
            for (int i = 0; i < intervals.length; i++)
                r2.add(String.format("%.2f", mu[j][i]));
            rows.add(r2);
        }
        tv.setItems(rows);
        tv.setPrefHeight(180);
        tv.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);
        return tv;
    }

    // ══════════════════════════════════════════════════════════════════════
    // Вкладка для переменной
    // ══════════════════════════════════════════════════════════════════════
    static Node buildVarTab(int[][][] expData, String[] intervals, String varName, String unit) {
        double[][] mu = calcMu(expData);

        // Заголовок
        Label title = new Label("Лингвистическая переменная: «" + varName + "»  (" + unit + ")");
        title.setFont(Font.font("SansSerif", FontWeight.BOLD, 14));
        title.setTextFill(Color.rgb(26, 58, 92));
        title.setPadding(new Insets(0, 0, 4, 0));

        // Формула
        Label formula = new Label("μ(uᵢ) = (1/K) · Σ bᵢⱼᵏ     |     K = 5 экспертов     |     b ∈ {0, 1}");
        formula.setFont(Font.font("Serif", FontPosture.ITALIC, 12));
        formula.setTextFill(Color.rgb(60, 80, 120));
        formula.setPadding(new Insets(4, 12, 4, 12));
        formula.setStyle("-fx-background-color: #eef5ff; -fx-border-color: #c8ddf0; -fx-border-radius:4; -fx-background-radius:4;");

        // График
        Canvas chart = buildChart(mu, intervals, varName, unit);

        // Таблица 1
        Label lbl1 = new Label("Таблица 1 — Мнения экспертов (бинарные оценки)");
        lbl1.setFont(Font.font("SansSerif", FontWeight.BOLD, 12));
        lbl1.setTextFill(Color.rgb(26, 58, 92));
        TableView<ObservableList<String>> t1 = buildExpertTableView(expData, intervals);

        // Таблица 2
        Label lbl2 = new Label("Таблица 2 — Степени принадлежности μ(u)");
        lbl2.setFont(Font.font("SansSerif", FontWeight.BOLD, 12));
        lbl2.setTextFill(Color.rgb(26, 58, 92));
        TableView<ObservableList<String>> t2 = buildMuTableView(mu, intervals);

        VBox tables = new VBox(8, lbl1, t1, lbl2, t2);
        tables.setPadding(new Insets(0, 6, 0, 0));

        HBox main = new HBox(16, tables, chart);
        main.setAlignment(Pos.TOP_LEFT);

        VBox root = new VBox(10, title, formula, main);
        root.setPadding(new Insets(14, 14, 14, 14));
        root.setStyle("-fx-background-color: #f4f7fb;");
        return root;
    }

    // ══════════════════════════════════════════════════════════════════════
    // Вкладка «О работе»
    // ══════════════════════════════════════════════════════════════════════
    static Node buildInfoTab() {
        TextArea ta = new TextArea();
        ta.setEditable(false);
        ta.setWrapText(true);
        ta.setFont(Font.font("Serif", 13));
        ta.setText(
                "ПРАКТИЧЕСКАЯ РАБОТА №6 — ВАРИАНТ 17\n" +
                        "═══════════════════════════════════════════════════\n\n" +
                        "Регион:    Санкт-Петербург\n" +
                        "Месяц:     Июнь («Белые ночи»)\n" +
                        "Специфика: Мало солнца, температура +12..+18°C, слабый ветер, умеренные осадки\n\n" +
                        "─── Климатические данные (исторические архивы 2020–2024) ────────────────\n" +
                        "  Температура:  мин +8°C,  средняя +16°C,  макс +25°C\n" +
                        "  Осадки:       мин 25 мм, средние 52 мм,  макс 90 мм/мес.\n" +
                        "  Скорость ветра: мин 1 м/с, средняя 3.6 м/с, макс 9 м/с\n\n" +
                        "─── Нечёткие переменные ──────────────────────────────────────────────────\n" +
                        "  1. Температура воздуха (°C) — 7 интервалов: от -5 до +30, шаг 5°C\n" +
                        "  2. Количество осадков (мм/мес.) — 7 интервалов: от 0 до 100 мм\n" +
                        "  3. Скорость ветра (м/с) — 7 интервалов: от 0 до 15 м/с\n\n" +
                        "  Лингвистические термы: «Низкий», «Средний», «Высокий»\n\n" +
                        "─── Метод построения МФ ─────────────────────────────────────────────────\n" +
                        "  Экспертный опрос: K = 5 специалистов\n" +
                        "    • Метеоролог\n" +
                        "    • Климатолог\n" +
                        "    • Местный житель\n" +
                        "    • Турист\n" +
                        "    • Гидролог\n\n" +
                        "  Бинарные оценки: b ∈ {0, 1}\n" +
                        "  Формула:  μ(uᵢ) = (1/K) · Σₖ bᵢⱼᵏ\n\n" +
                        "─── Аппроксимация МФ ────────────────────────────────────────────────────\n" +
                        "  Крайние термы (Низкий/Высокий) → Трапецеидальная функция МФ(x; a,b,c,d)\n" +
                        "  Средний терм                   → Треугольная МФ(x; a,b,c)\n" +
                        "                                   или Гауссова МФ(x) = exp[−((x−c)/σ)²]\n\n" +
                        "─── Выводы ──────────────────────────────────────────────────────────────\n" +
                        "  Июньский климат Санкт-Петербурга характеризуется:\n" +
                        "  — ТЕМПЕРАТУРА: высокая принадлежность к терму «Средняя» (интервалы 10–20°C)\n" +
                        "  — ОСАДКИ:      высокая принадлежность к терму «Средние» (35–65 мм/мес.)\n" +
                        "  — ВЕТЕР:       высокая принадлежность к терму «Слабый» (0–4 м/с)\n" +
                        "  Это подтверждает характеристику месяца: мягкий, нестабильный, влажный сезон."
        );
        ta.setStyle("-fx-background-color: #f8fbff; -fx-border-color: #c8ddf0;");

        VBox box = new VBox(ta);
        box.setPadding(new Insets(14));
        box.setStyle("-fx-background-color: #f4f7fb;");
        VBox.setVgrow(ta, Priority.ALWAYS);
        return box;
    }

    // ══════════════════════════════════════════════════════════════════════
    // Главное окно
    // ══════════════════════════════════════════════════════════════════════
    @Override
    public void start(Stage stage) {
        // Шапка
        VBox header = new VBox(3);
        header.setPadding(new Insets(14, 20, 14, 20));
        header.setStyle("-fx-background-color: linear-gradient(to right, #1A3A5C, #2E6DA4);");

        Label hTitle = new Label("Нечёткие функции принадлежности — Погода в Санкт-Петербурге, Июнь");
        hTitle.setFont(Font.font("SansSerif", FontWeight.BOLD, 17));
        hTitle.setTextFill(Color.WHITE);

        Label hSub = new Label("Практическая работа №6 · Вариант 17 · «Белые Ночи» · 5 экспертов · 7 интервалов · 3 терма");
        hSub.setFont(Font.font("SansSerif", 11));
        hSub.setTextFill(Color.rgb(180, 210, 240));

        header.getChildren().addAll(hTitle, hSub);

        // Вкладки
        TabPane tabs = new TabPane();
        tabs.setStyle("-fx-background-color: #f4f7fb;");
        tabs.setTabClosingPolicy(TabPane.TabClosingPolicy.UNAVAILABLE);

        Tab t1 = new Tab("🌡  Температура (°C)", buildVarTab(TEMP_EXP, TEMP_INT, "Температура воздуха", "°C"));
        Tab t2 = new Tab("🌧  Осадки (мм/мес.)", buildVarTab(PRECIP_EXP, PRECIP_INT, "Количество осадков", "мм/мес."));
        Tab t3 = new Tab("💨  Ветер (м/с)",       buildVarTab(WIND_EXP, WIND_INT, "Скорость ветра", "м/с"));
        Tab t4 = new Tab("ℹ  О работе",           buildInfoTab());

        tabs.getTabs().addAll(t1, t2, t3, t4);

        BorderPane root = new BorderPane();
        root.setTop(header);
        root.setCenter(tabs);

        Scene scene = new Scene(root, 1180, 660);
        stage.setTitle("Практическая работа №6 — Вариант 17: Санкт-Петербург, Июнь");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}