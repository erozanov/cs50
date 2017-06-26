<?php

    // configuration
    require("../includes/config.php"); 

    $rows = CS50::query("SELECT * FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
   
    
    $positions = [];
    foreach ($rows as $row)
    {
        $price = number_format($row["price"], 2, '.', ',');
        $positions[] = [
            "name" => $row["name"],
            "price" => "$" . $price,
            "shares" => $row["shares"],
            "symbol" => $row["symbol"], 
            "total" => number_format($row["shares"] * $row["price"], 2, '.', ',')
        ];
    }
    
    $rows = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    
    if(count($rows != 0))
    {
        $positions[] = [
            "name" => "",
            "price" => "",
            "shares" => "",
            "symbol" => "CASH", 
            "total" =>  number_format($rows[0]["cash"], 2, '.', ',')
        ];
        
    }
    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions]);
?>

