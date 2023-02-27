<?php

use GoogleSheets\Reports\Report;

require 'GoogleSheets/Reports.php';

// Format : <Time> <Date> <Month> <Year>
// Example : 6.30 PM 4 February 2023
$startDate = ''; //Start time
$endDate = ''; //End Time
$tabName = ''; //Tab Name in a spreadsheet ; Format : Feb 27, 2023 - EVENING

$bot = new \GoogleSheets\Reports\Report($startDate, $endDate, $tabName);