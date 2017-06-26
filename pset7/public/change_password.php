<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("change_password_form.php", ["title" => "Password Change"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["password"]) || empty($_POST["confirmPassword"]))
        {
            apologize("You must fill all fields.");
        }
        else if ($_POST["password"] != $_POST["confirmPassword"])
        {
            apologize("Passwords don't match");
        }

        // query database for user
        $rows = CS50::query("UPDATE users SET hash = ? WHERE id = ?", password_hash($_POST["password"], PASSWORD_DEFAULT), $_SESSION["id"]);


        // else success
        render("change_password_success.php", ["title" => "Portfolio"]);
    }

?>
