<?php
    // configuration
    require("../includes/config.php"); 

    $rows = CS50::query("SELECT * FROM history WHERE user_id = ?", $_SESSION["id"]);
    
    $positions = [];
    foreach ($rows as $row)
    {
        $price = number_format($row["price"], 2, '.', ',');
        $positions[] = [
            "transaction" => $row["transaction"],
            "date" =>  date_format(date_create($row["created"]), 'Y-m-d H:i'),
            "symbol" => $row["symbol"], 
            "shares" => $row["shares"],
            "price" => "$" . $price,

        ];
    }
    render("history_table.php", ["title" => "History", "positions" => $positions ]);

?>