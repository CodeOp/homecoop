<?php

if(realpath(__FILE__) == realpath($_SERVER['SCRIPT_FILENAME']))
   return;

//output storage area row in pickup location admin page
class HtmlStorageArea {
  
  const PROPERTY_STORAGE_AREA = "StorageArea";
  const PROPERTY_LINE_NUMBER = "LineNumber";
  const PROPERTY_REQUIRED = "Required";
  const PROPERTY_IS_NEW = "IsNew";
  const CTL_NAME_PREFIX = 'txtStorageAreaName_';
  const CTL_NEW_NAME_PREFIX = 'txtnewStorageAreaName_';
  const CTL_DISABLED_PREFIX = 'ctlSAIsDisabled_';
  const CTL_NEW_DISABLED_PREFIX = 'ctlnewSAIsDisabled_';
  const CTL_DELETE_PREFIX = 'chkDeleteStorageArea_';
  const CTL_MAX_BURDEN_PREFIX = 'txtMaxBurden_';
  const CTL_NEW_MAX_BURDEN_PREFIX = 'txtnewMaxBurden_';
  const CTL_DEFAULT_GROUP = 'radDefaultStorage';
  const CTL_DEFAULT_PREFIX = 'radDefaultStorage_';
  const CTL_NEW_DEFAULT_PREFIX = 'radnewDefaultStorage_';
  const CTL_THIRDROW = 'thirdrow_';
  
  const MIN_NEW_CONTROLS_NUM = 2000000000;
    
  protected $m_aData = array( self::PROPERTY_STORAGE_AREA => NULL,
                              self::PROPERTY_LINE_NUMBER => 1,
                              self::PROPERTY_IS_NEW => FALSE,
                              self::PROPERTY_REQUIRED => TRUE,
                      );
  
  public function __construct($arrSAID = NULL, $nLineNumber = 1) {
    $this->m_aData[self::PROPERTY_STORAGE_AREA] = $arrSAID;
    $this->m_aData[self::PROPERTY_LINE_NUMBER] = $nLineNumber;
  }
  
  public function __get( $name ) {
      switch ($name)
      {
        default:
          if ( array_key_exists( $name, $this->m_aData) )
            return $this->m_aData[$name];
          $trace = debug_backtrace();
          throw new Exception(
              'Undefined property via __get(): ' . $name .
              ' in class '. get_class() .', file ' . $trace[0]['file'] .
              ' on line ' . $trace[0]['line']);
          break;
      }
    }
    
    public function __set( $name, $value ) {
      switch ($name)
      {
        default:
        if (array_key_exists( $name, $this->m_aData))
        {
            $this->m_aData[$name] = $value;
             return;
        }
        $trace = debug_backtrace();
        throw new Exception(
            'Undefined property via __set(): ' . $name .
            ' in class '. get_class() .', file ' . $trace[0]['file'] .
            ' on line ' . $trace[0]['line']);
        break;
      }
    }
    
    public function GetHtml(&$initWeight)
    {
      $arrContent = array();
      
      $txtStorage = array(
        'element' => array(
          '#type' => 'textfield',
          '#required' => $this->m_aData[self::PROPERTY_REQUIRED],
        )
      );
      $said  = 0;
      $oNewValue = NULL;
      $idElement = NULL;
      $prefix = NULL;
      $initWeight += 10;
      $is_cheched = FALSE;
      
      $idnumber = NULL;
      if ($this->m_aData[self::PROPERTY_IS_NEW])
      {
        $txtStorage['ID'] = self::CTL_NEW_NAME_PREFIX . $this->m_aData[self::PROPERTY_LINE_NUMBER];
        $idnumber = $this->m_aData[self::PROPERTY_LINE_NUMBER];
        $txtStorage['title'] = '<!$LBL_NEW_STORAGE_AREA$!>';
      }
      else
      {
        $said = $this->m_aData[self::PROPERTY_STORAGE_AREA]['StorageAreaKeyID'];
        $idnumber = $said;
        $txtStorage['ID'] = self::CTL_NAME_PREFIX . $said;
        $txtStorage['title'] = sprintf('<!$FIELD_STORAGE_AREA_INDEX$!>', $this->m_aData[self::PROPERTY_LINE_NUMBER]);        
      }
      
      if (isset($this->m_aData[self::PROPERTY_STORAGE_AREA]['Names'])) {
        $txtStorage['values'] = $this->m_aData[self::PROPERTY_STORAGE_AREA]['Names'];
      }
      
      $arrContent['storagenames_' . $txtStorage['ID']] = array(
        '#prefix' => '<div class="resgridrow">',
        '#suffix' => '</div>',
        '#weight' => $initWeight,
        'names' => codeop_util_multilang_element($txtStorage),
      );
      
      
      $initWeight += 10;
      $oNewValue = NULL;
      if ($this->m_aData[self::PROPERTY_IS_NEW])
      {  
        if (isset($this->m_aData[self::PROPERTY_STORAGE_AREA]['fMaxBurden']))
          $oNewValue = check_plain($this->m_aData[self::PROPERTY_STORAGE_AREA]['fMaxBurden']);
        $idElement = self::CTL_NEW_MAX_BURDEN_PREFIX . $this->m_aData[self::PROPERTY_LINE_NUMBER];
      }
      else
      {
        $oNewValue = $this->m_aData[self::PROPERTY_STORAGE_AREA]['fMaxBurden'];
        $idElement = self::CTL_MAX_BURDEN_PREFIX . $said;
      }
      
      $arrContent[$idElement] = array(
          '#type' => 'textfield',
          '#weight' => $initWeight,
          '#title' => '<!$FIELD_MAX_STORAGE_BURDEN$!>',
          '#maxlength' => 10,
          '#size' => 25,
          '#default_value' => $oNewValue,
          '#rules' => array('numeric'),
          '#number_type' => 'decimal',
          '#description' => '<!$TOOLTIP_STORAGE_AREA_MAX_BURDEN$!>',
      );
      
      $thirdrow= self::CTL_THIRDROW .  $idnumber;
      
      $initWeight += 10;
      $arrContent[$thirdrow] = array(
        '#prefix' => '<div class="resgridrow">',
        '#suffix' => '</div>',
        '#weight' => $initWeight,
      );
      
      if ($this->m_aData[self::PROPERTY_IS_NEW]) {
        $oNewValue = FALSE;
        $idElement = self::CTL_NEW_DISABLED_PREFIX . $this->m_aData[self::PROPERTY_LINE_NUMBER];
        if (isset($this->m_aData[self::PROPERTY_STORAGE_AREA]['bDisabled'])) {
          $oNewValue = $this->m_aData[self::PROPERTY_STORAGE_AREA]['bDisabled'];
        }
        
        $prefix = '<div class="resgridfirstcell">';
      }
      else {
        $oNewValue = $this->m_aData[self::PROPERTY_STORAGE_AREA]['bDisabled'];
        $idElement = self::CTL_DISABLED_PREFIX . $said;
        $prefix = '<div class="resgridcell">';
        
        $arrContent[$thirdrow][self::CTL_DELETE_PREFIX .  $said] = array(
            '#prefix' => '<div class="resgridfirstcell">',
            '#suffix' => '</div>',
            '#type' => 'checkbox',
            '#id' => self::CTL_DELETE_PREFIX .  $said,
            '#title' => '<!$MARK_FOR_DELETE$!>',
            '#weight' => 10,
            '#attributes' => array('class' => array('resgriddatatiny')),
        );
      }
      
      $arrContent[$thirdrow][$idElement] = array(
            '#prefix' => $prefix,
            '#suffix' => '</div>',
            '#id' => $idElement,
            '#type' => 'select',
            '#key_type' => 'associative',
            '#title' => t('Status'),
            '#default_value' => $oNewValue,
            '#options' => array(0 => t('Active'), 1 => t('Inactive')),
            '#weight' => 20,
            '#attributes' => array('class' => array('resgriddata')),
      );

      $is_cheched = FALSE;
      if ($this->m_aData[self::PROPERTY_IS_NEW])
      {
        $idnumber += self::MIN_NEW_CONTROLS_NUM;
        $idElement = self::CTL_NEW_DEFAULT_PREFIX . $this->m_aData[self::PROPERTY_LINE_NUMBER];
        if ($this->m_aData[self::PROPERTY_LINE_NUMBER] == 1) {
          $is_cheched = TRUE;
        }
      }
      else
      {
        $idElement = self::CTL_DEFAULT_PREFIX . $said;

        if ($this->m_aData[self::PROPERTY_STORAGE_AREA]['bDefault']) {
          $is_cheched = TRUE;
        }
      }
      
      $arrContent[$thirdrow][$idElement] = array(
            '#prefix' => '<div class="resgridcell">',
            '#suffix' => '</div>',
            '#id' => $idElement,
            '#type' => 'radio',
            '#name' => self::CTL_DEFAULT_GROUP,
            '#title' => '<!$LBL_DEFAULT_STORAGE_AREA$!>',
            '#weight' => 30,
            '#attributes' => array(
              'class' => array('resgriddatatiny'),
              'value' => $idnumber,
            ),
      );
      
      if($is_cheched) {
        $arrContent[$thirdrow][$idElement]['#attributes']['checked'] = 'true';
      }
      
      if (isset($this->m_aData[self::PROPERTY_STORAGE_AREA]['bDefault']) && $this->m_aData[self::PROPERTY_STORAGE_AREA]['bDefault'])
          $arrContent[$thirdrow][$idElement]['#default_value'] = '1';
      
      return $arrContent;
    }  
}

?>
