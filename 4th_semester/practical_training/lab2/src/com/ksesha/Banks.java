package com.ksesha;

public enum Banks {
    PRIORBANK, BPS_SBERBANK, BELARUSBANK, BELGAZPROMBANK;

    @Override
    public String toString() {
        switch (this) {
            case PRIORBANK:
                return "Priorbank";
            case BPS_SBERBANK:
                    return "BPS-Sberbank";
            case BELARUSBANK:
                    return "Belarusbank";
            case BELGAZPROMBANK:
                return "Belgazprombank";
            default:
                    return "Undefined";
            }
        }

    public Banks getType(String type) throws IllegalArgumentException {
        Banks bank;
        switch (type) {
            case "Priorbank":
                bank = PRIORBANK;
                break;
            case "BPS-Sberbank":
                bank = BPS_SBERBANK;
                break;
            case "Belarusbank":
                bank = BELARUSBANK;
                break;
            case "Belgazprombank":
                bank = BELGAZPROMBANK;
                break;
            default:
                throw new IllegalArgumentException("Undefined bank");
            }
            return bank;
        }
}
