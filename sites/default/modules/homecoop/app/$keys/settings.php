<?php

if(realpath(__FILE__) == realpath($_SERVER['SCRIPT_FILENAME']))
   return;

//show errors
error_reporting(E_ALL);
ini_set('display_errors', '1');

//SUPPORED LANGUAGES
//first value in each array is the language-specifc folder that is created by create-language-folders.py
//second value in each array is the language display name, normally written in the language itself to ease identifying the switch option
//
//Each language's array element includes: 
//language folder (array key), 
//language name, 
//is a required language? (false=optional), 
//rtl/ltr align
//language id (from db)
//falling language id (from db. language to look in when a string is not found in the current langauge)

//SET TO NULL FOR NO LANGUAGE DIRS. Otherwise, the langauge key is added to the path.
$GLOBALS['g_aSupportedLanguages'] = array( 
                    'he' => array('עברית', true, 'rtl',2, 1), 
                    'en' => array('English', true, 'ltr', 1, 0) 
 );

global $g_aSupportedLanguages;

$GLOBALS['g_nCountLanguages'] = is_array($g_aSupportedLanguages)? count($g_aSupportedLanguages): 0;



//db access
define('DB_HOST',  '127.0.01');
define('DB_NAME',  'HomeCoop');
define('DB_CONNECTION_STRING',  'mysql:host=' . DB_HOST . ';dbname=' . DB_NAME);
define('DB_USERNAME',  'coopwebuser');
define('DB_PASSWORD',  'rubby');

//timezones. for other timezones see http://php.net/manual/en/timezones.php
define('COOP_TIMEZONE',  'Europe/Athens');

define('HOMECOOP_RECORDS_PER_PAGE', '25');
define('HOMECOOP_PAGER_PAGES', '9');
define('HOMECOOP_DATE_FORMAT', 'j.n.Y');
define('HOMECOOP_DATE_TIME_FORMAT', 'j.n.Y G:i');

//leave empty for no join page link
define('JOIN_PAGE', '');

//relative to language root
define('URL_UPLOAD_DIR', '../uploadimg/' );

//address to turn to in case of a no-balance inquiry
define('COOP_ADDRESS_MEMBER_BALANCE', 'admin@myhomecoop.org'); 
//address to turn to if a user has a login problem
define('COOP_ADDRESS_MEMBER_PERMISSIONS', 'admin@myhomecoop.org');

//when PAYMENT_METHOD_PLUS_EXTRA is used, the default percentage above balance
define ('DEFAULT_PERCENT_OVER_BALANCE_FOR_NEW_MEMBERS', 10);

define ('ENFORCE_UNIQUE_MAIN_EMAIL', TRUE);

define ('HOME_PAGE_SHOW_PRODUCER_CAPACITIES', FALSE);

define ('HOME_PAGE_SHOW_PICKUP_LOCATION_CAPACITIES', FALSE);

//allowed file types for product upload
define ('PRODUCT_IMAGE_MIME_TYPES', 'image/gif;image/jpeg;image/png');

//product picture max size in bytes
define ('PRODUCT_IMAGE_MAX_FILE_SIZE', 512000); //500KB

//means that the catalog can be accessed without login (has caching, so no performance concern)
define ('PRODUCT_CATALOG_IS_PUBLIC', TRUE);
//used in product.php to show/hide producer price for the viewed product
define ('SHOW_PRODUCER_PRICES_IN_PRODUCT_OVERVIEW', TRUE);
//used in catalog.php to show/hide producer prices for each product
define ('SHOW_PRODUCER_PRICES_IN_PRODUCT_CATALOG', TRUE);

//whether member roles can be changed through the system UI
//set this flag to FALSE to somewhat restrict the damage someone can do with an admin password
define ('ALLOW_ROLES_MODIFICATIONS', TRUE);

//for how long would the public (without login) version of the product page be cached (rendered without recreating it dynamically)
//since this page is dependant on database data, it is recommended to set this value to no more than 24 hours
define ('PRODUCT_CATALOG_CACHING', 86400); //24 hours

//member password minimum length
define ('PASSWORD_MIN_LENGTH', 6);

//use a different page to display errors, to avoid potential permissions breaches
define ('USE_ERROR_PAGE', TRUE);

//used to store the uploaded file in a specific name pattern
define ('PRODUCT_IMAGE_UPLOAD_FILE_NAME_TEMPLATE', 'prod%1$sPic%2$s');

//dimenstion of the pictures in product screen
define ('PRODUCT_IMAGE_HEIGHT_SMALL', 200);

//Any datetime format supported by the database
define('DATABASE_DATE_FORMAT','Y-m-d G:i:s');

//save users password unencrtypted in a separate sPasswordForMigration field
define ('MIGRATION_MODE', FALSE);

//---------------------- language switcher
//language switcher consts
define("LANGUAGE_SWITCHER_VALUE_LINKS", 0); //all languages will be displayed as side-by-side links
define("LANGUAGE_SWITCHER_VALUE_DROPDOWN", 1); //all languages will be displayed in a dropdown
//Langauge switcher control type: no need to change for one-language deployment
//possible values: 
//"SELECT" (a dropdown will be used for all supported languages that are not the current language)
//"LINKS" (an Html link will be displayed for each supported language that is not the current language)
define("LANGUAGE_SWITCHER", LANGUAGE_SWITCHER_VALUE_LINKS );
//----------------------

$GLOBALS['g_oTimeZone'] = new DateTimeZone(COOP_TIMEZONE);
global $g_oTimeZone;
$GLOBALS['g_dNow'] = new DateTime( "now", $g_oTimeZone );
global $g_dNow;

//language
define('LANG_PARAM', 'lang' );

//-------------- get the current language 
//according to the SCRIPT_FILENAME path, 
//without knowing ahead which languages are supported
//based on it, the relative path towards root, autoload function and language-switch capability are also defined

//$g_sRedirectAfterLangChange = '';
$GLOBALS['g_sRootRelativePath'] = url('', array('absolute' => TRUE)) . '/';
global $g_sRootRelativePath;

$GLOBALS['g_sFilePathFromRoot'] = current_path();

$GLOBALS['g_nCurrentLanguageID'] = 0;
$GLOBALS['g_nFallingLanguageID'] = 0;



define('SITE_ROOT', DRUPAL_ROOT . '/' . drupal_get_path('module', 'homecoop') . "/app" );


$GLOBALS['g_sLangDir'] = '';
if ($language->language != LANGUAGE_NONE) {
  $GLOBALS['g_sLangDir'] = $language->language;
}

global $g_sLangDir;

//set the root dir to be used in php includes
define('APP_DIR', SITE_ROOT . "/$g_sLangDir" );

//this function spares the need to include_once files when using app-level classes throught the system
function homecoop_autoload_class( $class_name ) {
  if (class_exists($class_name) || interface_exists($class_name)) {
    return TRUE;
  }
 
  if (stripos($class_name, '_mysql') !== FALSE) {
    return FALSE;
  }
  
  include_once APP_DIR . "/class/$class_name.php";
  return TRUE;
}

spl_autoload_register('homecoop_autoload_class');

                                          // !!!!!  Note: !!!!!
        // !!! All the below code must be located after the __autoload function has been defined
        // !!! because it accesses some app-level classes 

//set current and falling language ids (used in SQLBase)
if ($g_sLangDir != '')
{
  $GLOBALS['g_nCurrentLanguageID'] = $g_aSupportedLanguages[$g_sLangDir][Consts::IND_LANGUAGE_ID];
  $GLOBALS['g_nFallingLanguageID'] = $g_aSupportedLanguages[$g_sLangDir][Consts::IND_FALLING_LANGUAGE_ID];
}

//-------------- extract the current language - end


//default payment method in the new member screen
//possible values: "PAYMENT_METHOD" constants from Consts class
define ('DEFAULT_PAYMENT_METHOD_FOR_NEW_MEMBERS', Consts::PAYMENT_METHOD_PLUS_EXTRA);

//default file format for exported data (members, cooperative order data)
define ('DEFAULT_EXPORT_FORMAT', Consts::EXPORT_FORMAT_MS_EXCEL_XML);

//Rounding
//possible values (as defined in class\Rounding):
//const ROUND_TYPE_DEFAULT = 0;
//const ROUND_TYPE_FLOOR = 1;
//const ROUND_TYPE_CEILING = 2;
//const ROUND_TYPE_ROUND_PRECISION_1 = 3;
//const ROUND_TYPE_ROUND_PRECISION_2 = 4;
//const ROUND_TYPE_NO_ROUND = 100;
define ('ROUND_SETTING_BURDEN', Rounding::ROUND_TYPE_ROUND_PRECISION_2);
define ('ROUND_SETTING_CAPACITY', Rounding::ROUND_TYPE_CEILING);
define ('ROUND_SETTING_ORDER_COOP_FEE', Rounding::ROUND_TYPE_ROUND_PRECISION_1);
define ('ROUND_SETTING_ORDER_ITEM_COOP_TOTAL', Rounding::ROUND_TYPE_ROUND_PRECISION_2);
define ('ROUND_SETTING_ORDER_COOP_TOTAL', Rounding::ROUND_TYPE_ROUND_PRECISION_1);
define ('ROUND_SETTING_DELIVERY_TOTAL', Rounding::ROUND_TYPE_CEILING);
define ('ROUND_SETTING_PRODUCER_TOTAL' , Rounding::ROUND_TYPE_CEILING);
define ('ROUND_SETTING_PRODUCER_COOP_TOTAL' , Rounding::ROUND_TYPE_ROUND_PRECISION_2);
define ('ROUND_SETTING_COOP_TOTAL', Rounding::ROUND_TYPE_ROUND_PRECISION_1);
define ('ROUND_SETTING_PRODUCT_PRODUCER_TOTAL', Rounding::ROUND_TYPE_ROUND_PRECISION_2);
define ('ROUND_SETTING_PRODUCT_COOP_TOTAL', Rounding::ROUND_TYPE_ROUND_PRECISION_1);

//copy order default date jump
define ('COPY_ORDER_DEFAULT_DATE_JUMP', Consts::COPY_ORDER_JUMP_WEEK);
//jump x weeks/months
define ('COPY_ORDER_JUMP', 5);

//handles a persistant connection to the database
$GLOBALS['g_oDBAccess'] = new DBAccess();

//handles exceptions/errors
$GLOBALS['g_oError'] = new ErrorHandler();
