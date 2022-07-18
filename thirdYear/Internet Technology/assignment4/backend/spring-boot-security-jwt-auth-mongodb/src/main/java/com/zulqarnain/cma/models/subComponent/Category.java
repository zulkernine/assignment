package com.zulqarnain.cma.models.subComponent;

public class Category implements Comparable {
    String name;
    int frequency;

    public void setFrequency(int frequency) {
        this.frequency = frequency;
    }

    public Category(String n, int f){
        this.name = n;
        frequency = f;
    }

    public Category(String n){
        this.name = n;
        frequency = 1;
    }

    public Category(){}

    public void setName(String name) {
        this.name = name;
    }

    void increment(){ frequency++; }

    public String getName() {
        return name;
    }

    public int getFrequency() {
        return frequency;
    }

    @Override
    public int compareTo(Object o) {
        Category c = (Category) o;
        return this.name.compareTo(c.name);
    }


}
