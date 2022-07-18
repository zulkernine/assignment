package com.zulqarnain.cma.models;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;

import javax.validation.constraints.Email;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.Size;

import com.zulqarnain.cma.models.subComponent.Category;
import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.DBRef;
import org.springframework.data.mongodb.core.mapping.Document;

@Document(collection = "users")
public class User {
  @Id
  private String id;

  @NotBlank
  @Size(max = 20)
  private String username;

  @NotBlank
  @Size(max = 50)
  @Email
  private String email;

  private double averagePrice;

  private String gender;

  private List<Category> categoryList;

  //List of cloth ids
  private Set<String> cart;
  private List<String> history;

  @NotBlank
  @Size(max = 120)
  private String password;

  @DBRef
  private Set<Role> roles = new HashSet<>();

  public User(String id, String username, String email, List<Category> categoryList, Set<String> cart, List<String> history, String password, Set<Role> roles) {
    this.id = id;
    this.username = username;
    this.email = email;
    this.categoryList = categoryList;
    this.cart = cart;
    this.history = history;
    this.password = password;
    this.roles = roles;
  }

  public User() {
  }

  public User(String username, String email, String password,String gender) {
    this.username = username;
    this.email = email;
    this.password = password;
    categoryList = new LinkedList<>();
    this.gender = gender;
    cart = new HashSet<>();
  }

  public String getGender() {
    return gender;
  }

  public void setGender(String gender) {
    this.gender = gender;
  }

  public List<String> getHistory() {
    if(history==null) {
      history = new LinkedList<>();
    }

    return history;
  }

  public void setHistory(List<String> history) {
    this.history = history;
  }

  public double getAveragePrice() {
    if(Double.isNaN(averagePrice)){
      averagePrice = 0;
    }
    return averagePrice;
  }

  public void setAveragePrice(double averagePrice) {
    this.averagePrice = averagePrice;
  }

  public Set<String> getCart() {
    if(cart == null) cart = new HashSet<>();

    return cart;
  }

  public void setCart(Set<String> cart) {
    this.cart = cart;
  }

  public String getId() {
    return id;
  }

  public void setId(String id) {
    this.id = id;
  }

  public String getUsername() {
    return username;
  }

  public void setUsername(String username) {
    this.username = username;
  }

  public String getEmail() {
    return email;
  }

  public void setEmail(String email) {
    this.email = email;
  }

  public String getPassword() {
    return password;
  }

  public void setPassword(String password) {
    this.password = password;
  }

  public Set<Role> getRoles() {
    return roles;
  }

  public void setRoles(Set<Role> roles) {
    this.roles = roles;
  }

  public List<Category> getCategoryList() {
    return categoryList;
  }

  public void setCategoryList(List<Category> categoryList) {
    this.categoryList = categoryList;
  }
}
