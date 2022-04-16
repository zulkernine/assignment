package mocker.zulqarnain.repository;

import mocker.zulqarnain.models.Cloth;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.mongodb.repository.MongoRepository;
import org.springframework.data.mongodb.repository.Query;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface ClothRepository extends MongoRepository<Cloth, String> {

    Page<Cloth> findAll(Pageable pageable);

    Page<Cloth> findClothsByNameIsLike(String name,Pageable pageable);

}
