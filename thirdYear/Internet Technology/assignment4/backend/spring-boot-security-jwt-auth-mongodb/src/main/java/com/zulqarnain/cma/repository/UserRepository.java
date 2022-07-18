package com.zulqarnain.cma.repository;

import java.util.Optional;

import com.zulqarnain.cma.models.User;
import org.springframework.data.mongodb.repository.MongoRepository;

import org.springframework.data.mongodb.repository.Query;

public interface UserRepository extends MongoRepository<User, String> {

  @Query(fields="{ 'password' : 0}")
  Optional<User> findByUsername(String username);

  @Query(value = "{ 'username' : ?0}")
  Optional<User> findByUsername2(String username);

  Boolean existsByUsername(String username);

  Boolean existsByEmail(String email);
}
