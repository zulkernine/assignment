<%@ page import="com.example.models.Offer" %>
<%@ page import="java.util.List" %>
<%@ page import="com.example.models.Airport" %>
<%@ page import="com.example.models.Journey" %>
<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page buffer="8192kb" autoFlush="true" %>
<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <title>Flighty</title>
    <link rel="canonical" href="https://getbootstrap.com/docs/5.1/examples/heroes/" />

    <!-- Bootstrap core CSS -->
    <link href="./assets/dist/css/bootstrap.min.css" rel="stylesheet" />

    <style>
        .bd-placeholder-img {
            font-size: 1.125rem;
            text-anchor: middle;
            -webkit-user-select: none;
            -moz-user-select: none;
            user-select: none;
        }

        @media (min-width: 768px) {
            .bd-placeholder-img-lg {
                font-size: 3.5rem;
            }
        }
    </style>

    <style>
        .scrolling-wrapper {
            overflow-x: auto;
        }

        body {
            background-color: black;
            color: #fff;
            font-family: "system-ui";
        }

        h1 {
            font-weight: 700;
            font-size: 3.4em;
        }

        .subtitle {
            font-size: 1.25em;
            opacity: 0.65;
        }

        .card-block {
            height: 300px;
            background-color: #fff;
            border: none;
            background-position: center;
            background-size: cover;
            transition: all 0.2s ease-in-out !important;
            border-radius: 24px;

        &:hover {
             transform: translateY(-5px);
             box-shadow: none;
             opacity: 0.9;
         }
        }

        .card-1 {
            background-color: #4158d0;
            background-image: linear-gradient(43deg,
            #4158d0 0%,
            #c850c0 46%,
            #ffcc70 100%);
        }

        .card-2 {
            background-color: #0093e9;
            background-image: linear-gradient(160deg, #0093e9 0%, #80d0c7 100%);
        }

        .card-3 {
            background-color: #00dbde;
            background-image: linear-gradient(90deg, #00dbde 0%, #fc00ff 100%);
        }

        .card-4 {
            background-color: #fbab7e;
            background-image: linear-gradient(62deg, #fbab7e 0%, #f7ce68 100%);
        }

        .card-5 {
            background-color: #85ffbd;
            background-image: linear-gradient(45deg, #85ffbd 0%, #fffb7d 100%);
        }

        .card-6 {
            background-color: #fa8bff;
            background-image: linear-gradient(45deg,
            #fa8bff 0%,
            #2bd2ff 52%,
            #2bff88 90%);
        }
    </style>

    <!-- Custom styles for this template -->
    <link href="heroes.css" rel="stylesheet" />
</head>

<body>
<main>
    <h1 class="visually-hidden">Heroes examples</h1>

    <div class="container-fluid">

        <div class="scrolling-wrapper row flex-row flex-nowrap mt-4 pb-4 pt-2">
            <% List<Offer> offers = (List<Offer>) request.getAttribute("offers");
                for(int i=0; i<offers.size();i++){ %>

            <div class="col-4">
                <div class="card card-block card-1">
                    <div class="card-body">
                        <h1 class="mt-3">
                            <%= offers.get(i).getSource() %> to <%= offers.get(i).getDestination() %>
                        </h1>
                        <p class="subtitle">Now fly at attractive fares starting</p>
                        <h2 class="col mt-3">₹ <%= offers.get(i).getPrice() %>*</h2>
                        <p class="subtitle mt-3">
                            <%= offers.get(i).getPaymentOffer() %>
                        </p>
                    </div>
                </div>
            </div>
            <%}%>

        </div>
    </div>

    <div class="container col-xl-10 col-xxl-8 px-4 py-5">
        <div class="row align-items-center g-lg-5 py-5">
            <div class="col-lg-7 text-center text-lg-start">
                <h1 class="display-4 fw-bold lh-1 mb-3">Flighty</h1>
                <p class="col-lg-10 fs-4">Book flights in a jiffy</p>
            </div>
            <div class="col-md-10 mx-auto col-lg-5">
                <form class="p-4 p-md-5 border rounded-3 bg-light" action="/search" method="get">
                    <div class="form-floating mb-3">
                        <div class="input-group mb-3">
                            <span class="input-group-text" id="basic-addon1">From</span>
                            <select class="form-select" aria-label="Source airport" aria-describedby="basic-addon1"
                                    name="sourceAirport">
                                <% List<Airport> airports = (List<Airport>) request.getAttribute("airports");
                                    for(int i=0; i<airports.size();i++){%>
                                <option value=<%=airports.get(i).getAirportCode() %> > <%= airports.get(i).getCity()
                                %> (<%= airports.get(i).getAirportCode() %>) </option>
                                <%}%>
                            </select>
                        </div>
                    </div>
                    <div class="form-floating mb-3">
                        <div class="input-group mb-3">
                            <span class="input-group-text" id="basic-addon2">To</span>
                            <select class="form-select" aria-label="Destination airport" aria-describedby="basic-addon2"
                                    name="destinationAirport">
                                <% for(int i=0; i<airports.size();i++){%>
                                <option value=<%=airports.get(i).getAirportCode() %> > <%= airports.get(i).getCity() %> (
                                    <%= airports.get(i).getAirportCode() %>) </option>
                                <%}%>
                            </select>
                        </div>
                    </div>
                    <div class="form-floating mb-3">
                        <div class="input-group mb-3">
                            <span class="input-group-text" id="basic-addon3">Date</span>
                            <input type="date" name="travelDate" class="form-control" placeholder="Date of travel"
                                   aria-describedby="basic-addon3" />
                        </div>
                    </div>
                    <div class="form-floating mb-3">
                        <div class="input-group mb-3">
                            <span class="input-group-text" id="basic-addon4">Passengers</span>
                            <input type="number" class="form-control" placeholder="Number of passengers"
                                   aria-describedby="basic-addon4" />
                        </div>
                    </div>
                    <button class="w-100 btn btn-lg btn-primary" type="submit">Search</button>
                </form>
            </div>
        </div>
    </div>

    <div class="container col-xl-10 col-xxl-8 px-4 py-5">
        <h2> ${sourceAirportCode} To ${destinationAirportCode} on ${travelDate} </h2>
        <h3> ${message} </h3>
        <div class="list-group">

            <% List<Journey> journeys = (List<Journey>) request.getAttribute("journeys");
                if(journeys!=null)
                for(int i=0; i<journeys.size();i++){ %>
            <a href="#" class="list-group-item list-group-item-action" aria-current="true">
                <div class="d-flex w-100 justify-content-between">
                    <h5 class="mb-1">
                        <%= journeys.get(i).getDepartureTime() %> - <%= journeys.get(i).getArrivalTime() %>
                    </h5>
                    <h5 class="mb-1">₹ <%= journeys.get(i).getFare() %>
                    </h5>
                </div>
                <div class="d-flex w-100 justify-content-between">
                    <%-- <small>6E-483</small>--%>
                </div>
                <div class="d-flex w-100 justify-content-between align-items-end">
                    <p class="mb-1">
                        <%= journeys.get(i).getDepartureTime() %> • Non-stop
                    </p>
                    <button type="button" class="btn btn-dark">Book Now</button>
                </div>
            </a>
            <%}%>
        </div>
    </div>
</main>

<script src="../assets/dist/js/bootstrap.bundle.min.js"></script>
</body>

</html>