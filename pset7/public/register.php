<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["username"]) || empty($_POST["password"])) 
        {
            apologize("Please fill the fields");
        }elseif ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Password mismatch");
        }
        //insert user to table users
        $res = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));

        if ($res == false)
        {
            apologize("Username exists. Try another one.");
        }
        
        $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
        $cur_id = $rows[0]["id"];
        $_SESSION["id"] = $cur_id;
        redirect("/");


    }

?>