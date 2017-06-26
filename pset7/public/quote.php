<?php
    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    } else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a symbol.");
        }
        
        $stock = lookup($_POST["symbol"]);
        
        $price = $stock["price"];
        $name = $stock["name"];
        $symbol = $stock["symbol"];
        
        if(empty($name) || empty($price))
        {
          apologize("Symbol not found."); 
        }else 
        {
          render("quote_price.php", ["symbol" => $symbol, "name" => $name, "price" => number_format($price, 2, '.', ',')]);
 
        }
        
    }


?>