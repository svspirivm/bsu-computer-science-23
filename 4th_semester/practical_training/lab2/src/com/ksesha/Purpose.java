package com.ksesha;

public enum Purpose {
    MORTGAGE, AUTOMOBILE, MICROLOAN, LEASING, BUSINESS;

    @Override
    public String toString() {
        switch (this) {
            case MORTGAGE:
                return "Mortgage";
            case AUTOMOBILE:
                return "Automobile";
            case MICROLOAN:
                return "Microloan";
            case LEASING:
                return "Leasing";
            case BUSINESS:
                return "Business";
            default:
                return "Undefined";
        }
    }

    public Purpose getType(String type) throws IllegalArgumentException {
        Purpose purpose;
        switch (type) {
            case "Mortgage":
                purpose = MORTGAGE;
                break;
            case "Automobile":
                purpose = AUTOMOBILE;
                break;
            case "Microloan":
                purpose = MICROLOAN;
                break;
            case "Leasing":
                purpose = LEASING;
                break;
            case "Business":
                purpose = BUSINESS;
                break;
            default:
                throw new IllegalArgumentException("Undefined");
        }
        return purpose;
    }
}
