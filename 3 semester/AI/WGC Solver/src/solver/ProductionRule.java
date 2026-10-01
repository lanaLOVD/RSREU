package solver;

import model.RiverSituation;

/**
 * Интерфейс для продукций (правил) преобразования состояний.
 */
public interface ProductionRule {

    /**
     * Проверяет, можно ли применить правило к данному состоянию.
     */
    boolean isApplicable(RiverSituation situation);

    /**
     * Применяет правило к состоянию и возвращает новое состояние.
     */
    RiverSituation apply(RiverSituation situation);

    /**
     * Возвращает стоимость применения правила.
     * Используется в Branch and Bound и A*.
     */
    int getCost();

    /**
     * Описание правила для отладки.
     */
    String getDescription();
}