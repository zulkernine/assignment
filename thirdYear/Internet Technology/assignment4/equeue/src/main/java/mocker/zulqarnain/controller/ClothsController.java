package mocker.zulqarnain.controller;

import mocker.zulqarnain.models.Cloth;
import mocker.zulqarnain.services.ClothServices;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
public class ClothsController {

    private final ClothServices clothServices;

    public ClothsController(ClothServices clothServices) {
        this.clothServices = clothServices;
    }

    @GetMapping("/api/cloth")
    public List<Cloth> getAllClothes(@RequestParam(required = false) String name,@RequestParam(defaultValue = "1") int pageNo,@RequestParam(defaultValue = "10") int pageSize){
        if(name==null)
            return clothServices.getAllClothes(pageNo-1,pageSize);
        else
            return clothServices.getAllClothesByName(name,pageNo-1,pageSize);
    }


}
