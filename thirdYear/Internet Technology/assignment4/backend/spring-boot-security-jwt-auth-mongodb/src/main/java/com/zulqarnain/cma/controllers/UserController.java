package com.zulqarnain.cma.controllers;

import com.zulqarnain.cma.models.User;
import com.zulqarnain.cma.repository.UserRepository;
import com.zulqarnain.cma.security.services.UserDetailsImpl;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.web.bind.annotation.*;

import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

@CrossOrigin(origins = "*", maxAge = 3600)
@RestController()
@RequestMapping("/api/user")
@PreAuthorize("hasRole('USER')")
public class UserController {

    @Autowired
    UserRepository userRepository;

    @GetMapping()
    User getUser(){
        String uname = ((UserDetailsImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal()).getUsername();
        System.out.println(uname);
        Optional<User> u = userRepository.findByUsername(uname);
        return u.orElse(null);
    }

    @GetMapping("/cart")
    Set<String> getCartClothIDs(){
        User u = getUser();
        if(u!=null){
            return u.getCart();
        }
        return new HashSet<>();
    }

    @GetMapping("/checkout")
    void checkout(@RequestParam(name = "average") double average){
        User u = getUser();
        System.out.println("average: "+average);

        if(u!=null){
            int h = u.getHistory().size(),c = u.getCart().size();
            u.getHistory().addAll(u.getCart());
            u.getCart().clear();
            double newAverage = (double) (h*u.getAveragePrice() + c*average)/(double) (c+h);
            u.setAveragePrice(newAverage);

            System.out.println(newAverage+" "+c+" "+h+" "+u.getAveragePrice());
            System.out.println(u.getAveragePrice());

            userRepository.save(u);
        }
    }

    @PostMapping("/cart/{id}")
    void addToCart(@PathVariable String id){
        User u = getUser();
        if(u!=null){
            u.getCart().add(id);
            userRepository.save(u);
        }
    }

}
