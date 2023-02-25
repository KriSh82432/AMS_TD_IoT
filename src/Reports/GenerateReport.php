<?php

use GoogleSheets\Reports\Report;

require 'GoogleSheets/Reports.php';

// Format : <Time> <Date> <Month> <Year>
// Example : 6.30 PM 4 February 2023
$startDate = '11 AM 25 February 2023';
$endDate = '5 PM 25 February 2023';
$tabName = 'Feb 25, 2023 - AFTERNOON';

$bot = new \GoogleSheets\Reports\Report($startDate, $endDate, $tabName);
