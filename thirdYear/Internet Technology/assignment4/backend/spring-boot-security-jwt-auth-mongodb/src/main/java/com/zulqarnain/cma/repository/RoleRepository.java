package com.zulqarnain.cma.repository;

import java.util.Optional;

import com.zulqarnain.cma.models.Role;
import com.zulqarnain.cma.models.subComponent.ERole;
import org.springframework.data.mongodb.repository.MongoRepository;

public interface RoleRepository extends MongoRepository<Role, String> {
  Optional<Role> findByName(ERole name);
}
