package mocker.zulqarnain.flight_server;

import com.google.gson.Gson;
import mocker.zulqarnain.dao.PersonDao;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.io.IOException;
import java.util.stream.Collectors;

@WebServlet(name = "PersonServlet", value = "/person")
public class PersonServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        PersonDao pDao = new PersonDao(request.getServletContext());

        response.setContentType("application/json");

        Gson gson = new Gson();

        response.getWriter().println(pDao.readAllPerson()
                .stream()
                .map(gson::toJson)
                .collect(Collectors.toList()));
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

    }
}
