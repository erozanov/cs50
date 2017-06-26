<?php
    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("buy_form.php", ["title" => "Buy"]);
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
          apologize("Symbol not found, please try another one."); 
        }else if(!preg_match("/^\d+$/", $_POST["shares"]))
          apologize("Shares invalid. Please write a valid number."); 
        {
            $total = $price * $_POST["shares"];
            
            $result = CS50::query("SELECT * FROM users WHERE ID = ?", $_SESSION["id"]);
        
            if (count($result) == 1) 
            {
                $res = $result[0];
                $cash = $res["cash"];
                if ($total > $cash)
                {
                 apologize(" You can't afford this count of shares.Please try another one."); 
                }else 
                {
                $result = CS50::query("INSERT INTO portfolios (user_id, symbol, shares, price, name) VALUES(?, ?, ?, ?, ? ) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $symbol, $_POST["shares"], $price, $name);
    
                
                if ($res == false)
                {
                        apologize("Error. Try another one.");
                }
                
                //update users cash
                $result = CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $total, $_SESSION["id"]);
                
                
                //update history
                $result = CS50::query("INSERT INTO history (transaction, created, symbol, shares, price, user_id) VALUES(?, now(), ?, ?, ?, ?)",  "BUY", $symbol, $_POST["shares"],  $price, $_SESSION["id"]);

                redirect("/");
                }
    
            }
        
        }
        
    }


?>