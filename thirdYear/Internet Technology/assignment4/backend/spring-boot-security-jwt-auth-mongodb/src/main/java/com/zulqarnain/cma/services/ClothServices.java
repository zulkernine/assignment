package com.zulqarnain.cma.services;

import com.zulqarnain.cma.models.Cloth;
import com.zulqarnain.cma.models.User;
import com.zulqarnain.cma.repository.ClothRepository;
import com.zulqarnain.cma.repository.UserRepository;
import com.zulqarnain.cma.security.services.UserDetailsImpl;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.mongodb.core.MongoOperations;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Service;

import java.util.*;

@Service
public class ClothServices {

    final ClothRepository clothsRepository;
    final UserRepository userRepository;
    private final MongoOperations mongoOperations;

    User getUser(){
        Object userDetail = SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if(userDetail.getClass()!=UserDetailsImpl.class) return null;

        String uname = ((UserDetailsImpl) userDetail).getUsername();
        System.out.println(uname);
        Optional<User> u = userRepository.findByUsername(uname);
        System.out.println(u.isPresent());
        return u.orElse(null);
    }

    public ClothServices(ClothRepository clothsRepository, UserRepository userRepository, MongoOperations mongoOperations) {
        this.clothsRepository = clothsRepository;
        this.userRepository = userRepository;
        this.mongoOperations = mongoOperations;
    }


    public List<Cloth> getAllClothes(int page, int size) {
        User u = getUser();
        List<String> tag = new ArrayList<>(List.of("New"));
        double maxPrice = 20000,minPrice = 0;
        if(u!=null){
            tag.add(u.getGender());
            double avg = u.getAveragePrice();
            if(avg>0){
                maxPrice = avg * 1.5;
                minPrice = avg * 0.4;
            }
        }

        List<Cloth> cloths = clothsRepository.findAll(tag,maxPrice,minPrice,PageRequest.of(page, size)).toList();
        if(cloths.isEmpty()){
            cloths = clothsRepository.findAll(tag,20000,0,PageRequest.of(page, size)).toList();
        }
        return cloths;
    }

    public List<Cloth> getAllClothesByName(String name, int page, int size) {
        return clothsRepository.findClothsByNameIsLike(name, PageRequest.of(page, size)).toList();
    }

    public Cloth getClothById(String id) {
        return clothsRepository.findClothById(id);
    }

    public List<Cloth> searchClothes(String searchText, int page, int size) {
        User u = getUser();
        String tag = (u!=null)?u.getGender():"New";

//        Query query = TextQuery.queryText(TextCriteria.forDefaultLanguage().matchingAny(searchText.split(" ")).caseSensitive(false)).sortByScore().with(PageRequest.of(page, size));
//        query.addCriteria(Criteria.where("categories").all(tag));
//        query.addCriteria(Criteria.where("discount").gt(0));

        return clothsRepository.findClothsBySearchtext(searchText,PageRequest.of(page, size)).toList();

//        return mongoOperations.find(query, Cloth.class);
    }

}
