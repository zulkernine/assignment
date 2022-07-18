package com.zulqarnain.cma.controllers;

import com.zulqarnain.cma.models.Cloth;
import com.zulqarnain.cma.security.services.UserDetailsImpl;
import com.zulqarnain.cma.services.ClothServices;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@CrossOrigin(origins = "*", maxAge = 3600)
@RestController()
@RequestMapping("/api/cloth")
public class ClothsController {

    private final ClothServices clothServices;

    public ClothsController(ClothServices clothServices) {
        this.clothServices = clothServices;
    }

    @GetMapping()
    public List<Cloth> getAllClothes(@RequestParam(name = "search",defaultValue = "") String serachText, @RequestParam(defaultValue = "1") int pageNo, @RequestParam(defaultValue = "12") int pageSize){
        if(serachText.isEmpty())
            return clothServices.getAllClothes(pageNo-1,pageSize);
        else
            return clothServices.searchClothes(serachText,pageNo-1,pageSize);
    }

    @GetMapping("/{id}")
    public Cloth getClothById(@PathVariable String id){
        return clothServices.getClothById(id);
    }

    boolean isUserLoggedIn(){
        return SecurityContextHolder.getContext().getAuthentication().getPrincipal() instanceof UserDetailsImpl;
    }


}
