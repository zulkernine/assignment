package mocker.zulqarnain.services;

import mocker.zulqarnain.models.Cloth;
import mocker.zulqarnain.repository.ClothRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.PageRequest;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class ClothServices {

    final ClothRepository clothsRepository;

    public ClothServices(ClothRepository clothsRepository) {
        this.clothsRepository = clothsRepository;
    }

    public List<Cloth> getAllClothes(int page,int size){
        return clothsRepository.findAll(PageRequest.of(page,size)).toList();
    }

    public List<Cloth> getAllClothesByName(String name,int page,int size){
        return clothsRepository.findClothsByNameIsLike(name,PageRequest.of(page,size)).toList();
    }
}
