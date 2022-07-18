package com.zulqarnain.cma.repository;

import com.zulqarnain.cma.models.Cloth;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.mongodb.repository.MongoRepository;
import org.springframework.data.mongodb.repository.Query;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface ClothRepository extends MongoRepository<Cloth, String> {

    @Query("{discount:{$gt:0}, categories: {$all: ?0 }, $and:[ {price: { $gte: ?2 }}, {price: { $lte: ?1 }} ] }")
    Page<Cloth> findAll(List<String> tags,double max,double min, Pageable pageable);

    Page<Cloth> findClothsByNameIsLikeAndDiscountGreaterThan(String name,int d,Pageable pageable);

    Page<Cloth> findClothsByNameIsLike(String name,Pageable pageable);

    Cloth findClothById(String id);

    @Query("{discount:{$gt:0}, $text:{$search: ?0}}")
    Page<Cloth> findClothsBySearchtext(String text,Pageable pageable);

}
