<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        $symbols = array();
        $result = CS50::query("SELECT symbol FROM portfolios WHERE USER_ID = ?", $_SESSION["id"]);
        
        if(count($result) == 0)
        {
            apologize("You don't have a sell");
        }else
        {
            foreach($result as $i)
            {
                $symbols[] = $i["symbol"];
            }
            render("sell_form.php", ["title" => "Sell", "symbols"=> $symbols]);
        }
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["symbol"])) 
        {
            apologize("error");
        }
        
        $result = CS50::query("SELECT * FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        if (count($result) == 0) 
        {
            apologize("error");

        }
        
        $price = $result[0]["price"];
        $shares = $result[0]["shares"];
        $total = $price * $shares;
        $symbol = $result[0]["symbol"];

        
        $result = CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);


        $result = CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $total, $_SESSION["id"]);
        
        //update history
        $result = CS50::query("INSERT INTO history (transaction, created, symbol, shares, price, user_id) VALUES(?, now(), ?, ?, ?, ?)",  "SELL", $symbol, $shares,  $price, $_SESSION["id"]);

        if ($result == false)
        {
            apologize("error");
        }
        
        redirect("index.php");


    }
