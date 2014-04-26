<?php

if(realpath(__FILE__) == realpath($_SERVER['SCRIPT_FILENAME']))
   return;

include_once APP_DIR . '/class/UserSession.php';
include_once APP_DIR . '/class/UserSessionBase.php';
include_once APP_DIR . '/class/Consts.php';

define('POST_ELM_LOGOUT','hidLogout');

if (!isset($GLOBALS['g_oMemberSession'])) {
  $GLOBALS['g_oMemberSession']= new UserSession ( );
}

global $g_oMemberSession;

global $g_sRootRelativePath;

if ($_SERVER[ 'REQUEST_METHOD'] == 'POST')
{
    //basic referer check for each post in the system
    if (  ! HttpRefererCheck::PerformCheck() )
    {
        UserSessionBase::Close();
        drupal_goto($g_sRootRelativePath . Consts::URL_ACCESS_DENIED);
        exit;
    }

    //process logout post request
    if (array_key_exists(POST_ELM_LOGOUT, $_POST)) {
      if ($_POST[ POST_ELM_LOGOUT ] )
      {
          $g_oMemberSession->Logout( );
          UserSessionBase::Close();
          drupal_goto($g_sRootRelativePath . Consts::URL_LOGIN);
          exit;
      }
    }
}

//authenticate user by checking session data
if (! $g_oMemberSession->Authenticate( ) )
{
    //not authenticated yet: add to login url a redirect instruction to desired page after login
    // . "?redr=" .  urlencode($_SERVER['PHP_SELF'] . "?" . $_SERVER['QUERY_STRING'] ) );
    
    UserSessionBase::Close();
    drupal_goto($g_sRootRelativePath . Consts::URL_LOGIN);
    
    exit;
}

