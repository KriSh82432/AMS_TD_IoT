<?php

namespace GoogleSheets\Reports;

use PDO;

require 'vendor/autoload.php';
require 'GSheetsBase.php';
require 'DB/DB.php';
require 'Config/Domain.php';

class Report
{
    // Format : <Time> <Date> <Month> <Year>
    // Example : 6.30 PM 4 February 2023
    private string $startDate;
    private string $endDate;
    private array $data;
    private string $tabName;
    private $bot;
    private array $failedList;

    public function __construct(string $startDate, string $endDate, string $tabName)
    {
        date_default_timezone_set('Asia/Kolkata');
        $this->startDate = strval(strtotime($startDate));
        $this->endDate = strval(strtotime($endDate));
        $this->tabName = $tabName;
        $this->bot = new \GoogleSheets\GSheetsBase\AMS(\GoogleSheets\Config\Credentials::credentialsPath, \GoogleSheets\Config\Credentials::reportsSheetId);
        $this->Run();
    }

    protected function Run()
    {
        $this->data = $this->GetData($this->startDate, $this->endDate);
        $row = [];
        if (count($this->data) != 0) {
            if ($this->CreateAndCheckTab()) {
                foreach ($this->data as $value) {
                    $value["Domain"] = \Config\Domain::ToLabel($value['Domain']);
                    $value["EntryTime"] = date('g:i A \a\t F j', $value["EntryTime"]);
                    $row[] = array_values($value);
                }
                $this->AddEntry($row);
            }
        } else {
            echo "No New Log. Bye\n";
            exit;
        }
    }

    protected function CreateAndCheckTab()
    {
        $response = $this->bot->CreateNewTab($this->tabName);

        if ($response->replies[0]->addSheet->properties->sheetId) {
            echo "Tab Created Successfully\n";
            return true;
        } else {
            echo "Couldn't create Tab\n";
            return false;
        }
    }

    protected function GetData(string $startDate, string $endDate)
    {
        $Sql = 'SELECT U.Name, U.Domain, E.EntryTime FROM EntryLogsTest E INNER JOIN Users U ON E.UID=U.UID WHERE EntryTime>=? AND EntryTime<=? ORDER BY EntryTime';
        $result = \DB\DbConn::Get()->PrepareAndExecute($Sql, [$startDate, $endDate]);
        return $result;
    }

    protected function AddHeader()
    {
        $data[] = [
            "Name",
            "Domain",
            "Logged Time"
        ];
        $response = $this->bot->AppendRow($this->tabName, $data);
        if ($response->updates->updatedRows == 1) {
            return true;
        } else {
            return false;
        }
    }

    public function AddEntry(array $data)
    {
        if ($this->AddHeader()) {
            $response = $this->bot->AppendRow($this->tabName, $data);
            if ($response->updates->updatedRows == count($data)) {
                echo "Rows inserted successfully\n";
            } else {
                echo "Some error occurred while inserting...\n";
            }
        } else {
            echo "Couldn't create Header\n";
        }
    }
}
