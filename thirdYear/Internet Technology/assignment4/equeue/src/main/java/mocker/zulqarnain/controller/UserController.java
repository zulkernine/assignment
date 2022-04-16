package mocker.zulqarnain.controller;

import org.springframework.security.core.annotation.AuthenticationPrincipal;
import org.springframework.security.oauth2.core.user.OAuth2User;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.security.Principal;
import java.util.Map;

@RestController
public class UserController {

    //Too much unnecessary data in Principal
//    @RequestMapping(value = "/user")
//    public Principal user(Principal principal) {
//        return principal;
//    }

    @RequestMapping(value = "/user")
    public Map<String, Object> userDetails(@AuthenticationPrincipal OAuth2User user) {
        return user.getAttributes();
    }

}
