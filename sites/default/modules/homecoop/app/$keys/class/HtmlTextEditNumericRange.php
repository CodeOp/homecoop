<?php

if(realpath(__FILE__) == realpath($_SERVER['SCRIPT_FILENAME']))
   return;

//outputs to html document a refined HtmlTextEdit for numbers with "up" and "down" buttons to increase or decrease the input number
class HtmlTextEditNumericRange extends HtmlTextEdit {
  
 const PROPERTY_INTERVAL = "Interval";
 const PROPERTY_MAX_VALUE = "MaxValue";
 const PROPERTY_SUBSEQUENT_TEXT = "SubsequentText";
  
 public function __construct($sId, $sDir, $nType, $sValue, $nInterval)
 {
   $this->m_aData = array(
         self::PROPERTY_ID => $sId,
         self::PROPERTY_DIR => $sDir,
         self::PROPERTY_TYPE => $nType,
         self::PROPERTY_REQUIRED => FALSE,
         self::PROPERTY_READ_ONLY => FALSE,
         self::PROPERTY_VALUE => $sValue,
         self::PROPERTY_MAX_LENGTH => NULL,
         self::PROPERTY_CSS_CLASS => NULL,
         self::PROPERTY_TEXTAREA_ROWS => NULL,
         self::PROPERTY_ENCLOSE_IN_HTML_CELL => FALSE,
         self::PROPERTY_INTERVAL => $nInterval,
         self::PROPERTY_MAX_VALUE => NULL,
         self::PROPERTY_ON_CHANGE => NULL,
         self::PROPERTY_SUBSEQUENT_TEXT => NULL,
         self::PROPERTY_PROPERTIES => array()
        );
 } 
 
 //output the onclick event for a button
 protected function OnClick($bUp)
 {
   if ($this->m_aData[self::PROPERTY_READ_ONLY])
     return '';
   
   $sOnClick = ' onclick="JavaScript:' .
    ' var ctl = document.getElementById(\'' . $this->m_aData[self::PROPERTY_ID] . '\'); ' .
    ' var nValue = 0; ' .
    ' if (ctl.value != null && !isNaN(parseFloat(ctl.value))) nValue = parseFloat(ctl.value); ';
   $nInterval = 1;
   if ($this->m_aData[self::PROPERTY_INTERVAL] != NULL && $this->m_aData[self::PROPERTY_INTERVAL] > 0) {
     $nInterval = $this->m_aData[self::PROPERTY_INTERVAL];
   }
   if ($bUp) {
     $sOnClick .= ' nValue = nValue +  ' . $nInterval . ';';
   }
   else {
     $sOnClick .= ' nValue = nValue -  ' . $nInterval . ';';
   }
   
   if ($this->m_aData[self::PROPERTY_MAX_VALUE] != NULL && $this->m_aData[self::PROPERTY_MAX_VALUE] > 0) {
    $sOnClick .= ' if (nValue > ' . $this->m_aData[self::PROPERTY_MAX_VALUE] . ' ) nValue = ' .
           $this->m_aData[self::PROPERTY_MAX_VALUE] . ';';
   }
   
   $sOnClick .= ' if (nValue < 0 ) nValue = 0;' .
    ' ctl.value = nValue;' .
    '" ';
   
   return $sOnClick;
 }
 
 //echo directly to html document to save some string concats/retrieval
 public function EchoHtml()
 {
   global $g_sRootRelativePath;
   
   echo  '<table cellspacing="0" cellpadding="0" border="0">' ,
      '<tr>',
      '<td><table cellspacing="0" cellpadding="0" border="0">',
        '<tr><td>';
   $this->EchoEditPartHtml();
   echo '</td></tr>',
      '</table></td>',
      '<td style="vertical-align:middle;"><table cellspacing="0" cellpadding="0" border="0" style="font-size: 1px;" >',
      '<tr><td><span  ' ,
  $this->OnClick(TRUE),
  ' class="btnrange"><img src="' , $g_sRootRelativePath , 'img/btnrangeup.gif" /></span></td></tr>',
    '<tr><td><span ',
  $this->OnClick(FALSE),
  'class="btnrange"><img src="' , $g_sRootRelativePath , 'img/btnrangedown.gif" /></span></td></tr>',
      '</table>',
      '</td></tr>';
   if ($this->m_aData[self::PROPERTY_SUBSEQUENT_TEXT] != NULL)   
    echo '<tr><td>' , $this->m_aData[self::PROPERTY_SUBSEQUENT_TEXT] , '</td></tr>';

   echo '</table>';
 }
 
  public function GetHtml() {
    global $HomeCoopThemePath;

    $arrContent = array(
      '#prefix' => '<table cellspacing="0" cellpadding="0" border="0">',
      '#suffix' => '</table>',
      'controlsrow' => array(
        '#prefix' => '<tr>',
        '#suffix' => '</tr>',
        'textpart' => array(
         '#prefix' => '<td><table cellspacing="0" cellpadding="0" border="0"><tr><td>',
         '#suffix' => '</td></tr></table></td>',
         $this->GetEditPartHtml(),
        ),
        'buttons' => array(
          '#prefix' => '<td style="vertical-align:middle;"><table cellspacing="0" cellpadding="0" border="0" style="font-size: 1px;" >',
          '#suffix' => '</table></td>',
          'upbutton' => array(
            '#prefix' => '<tr><td><span  ' . $this->OnClick(TRUE) . ' class="btnrange">',
            '#markup' => '<img src="' . $HomeCoopThemePath . 'img/btnrangeup.gif" />',
            '#suffix' => '</span></td></tr>',
          ),
          'downbutton' => array(
            '#prefix' => '<tr><td><span  ' . $this->OnClick(FALSE) . ' class="btnrange">',
            '#markup' => '<img src="' . $HomeCoopThemePath . 'img/btnrangedown.gif" />',
            '#suffix' => '</span></td></tr>',
          ),
        ),
     ),
   );
   
   if ($this->m_aData[self::PROPERTY_SUBSEQUENT_TEXT] != NULL)  {
    $arrContent['secondrow'] = array(
      '#prefix' => '<tr><td>',
      '#markup' => $this->m_aData[self::PROPERTY_SUBSEQUENT_TEXT],
      '#suffix' => '</td></tr>',
    );
   }
   return $arrContent;
 }
 
}

?>
