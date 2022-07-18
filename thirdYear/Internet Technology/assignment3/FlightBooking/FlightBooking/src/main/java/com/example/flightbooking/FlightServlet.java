package com.example.flightbooking;

import com.example.dao.AirportDAO;
import com.example.dao.JourneysDao;
import com.example.dao.OfferDAO;
import com.example.models.Airport;
import com.example.models.Journey;
import com.example.models.Offer;

import java.io.*;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Locale;
import javax.servlet.ServletException;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "FlightServlet",urlPatterns = {"/search"})
public class FlightServlet extends HttpServlet {
    private String message;

    public void init() {
        message = "Hello World!";
//        getServletContext().getAttribute()

    }

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

        String src = request.getParameter("sourceAirport");
        String dest = request.getParameter("destinationAirport");
        String date = request.getParameter("travelDate");

        if(date!=null && src!=null && dest!=null){
//            System.out.println( date+"\t"+src+"\t"+dest );

            SimpleDateFormat format1 = new SimpleDateFormat("yyyy-MM-dd");
            Date dt1 = null;
            try {
                dt1 = format1.parse(date);
            } catch (ParseException e) {
                e.printStackTrace();
            }

            if(dt1!=null){
                DateFormat formatter = new SimpleDateFormat("EEEE", Locale.getDefault());
                String day = formatter.format(dt1);
                System.out.println( day+"\t"+src+"\t"+dest );

                List<Journey> journeys = new JourneysDao(request.getServletContext()).getAvailableJourneys(src,dest,day);
//                System.out.println(journeys);

                request.setAttribute("sourceAirportCode",src);
                request.setAttribute("destinationAirportCode",dest);
                request.setAttribute("travelDate",date);

                if(!journeys.isEmpty()){
                    request.setAttribute("journeys",journeys);
                    request.setAttribute("message", journeys.size() + " Flights found");
                }else{
                    request.setAttribute("message","No Flights found :( ");
                }
            }
        }


//        HttpSession hs = request.getSession();
//        hs.se

        // Set banners
        OfferDAO offerDAO = new OfferDAO(request.getServletContext());
        List<Offer> offers = offerDAO.readAllOffers();
        System.out.println("Offers: " +offers.size());
        List<Airport> airports = new AirportDAO(request.getServletContext()).readAllAirports();
//        System.out.println(offers);
        request.setAttribute("offers", offers);
        request.setAttribute("airports", airports);

        response.setContentType("text/html");
        getServletContext().getRequestDispatcher("/index.jsp").forward(request, response);
    }


    public void destroy() {
    }
}