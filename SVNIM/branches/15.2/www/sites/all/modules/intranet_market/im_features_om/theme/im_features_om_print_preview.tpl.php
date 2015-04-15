<?php
/**
 * @file
 * Rendering the Operational model node content in a print format
 */
hide($node->comments);
hide($node->links);
drupal_add_js('jQuery(document).ready(function () { window.print(); jQuery("#columns").attr("id", "column"); jQuery("#skip-link").html(); jQuery("#skip-link").remove(); jQuery("#header").html(); jQuery("#header").remove(); });', 'inline');
//To theme operational model detailed view
  drupal_add_css(drupal_get_path('module', 'im_features_om') . '/css/om.css');
  //To add jquery for left side menu and show content
  drupal_add_js(drupal_get_path('module', 'im_features_om') . '/js/om.js');
?>
<div class="node node-operational-model article clearfix" id="operational-model" style="background-color: #FFF">
<div class="om-right-sec-print-preview">
        <div class="white-boxes">
      <?php if (!empty($node->field_om_access['und'][0]['value'])): ?>
          <div class="om-right-block">
           <h3 class="om-right-title"><?php print t("Fontions Concernees");?></h3>
           <div class="om-right-content om-access">
           <div class="field field-name-field-om-actuers field-type-taxonomy-term-reference field-label-hidden view-mode-full"><ul class="field-items">
           <?php 
           $actuers = $node->field_om_actuers['und'];
           for ($i=0; $i<count($actuers); $i++) {
             if ($i % 2 == 0) {
               $class = "even";
             }
             else {
               $class = "odd";
             }
             $actuers_term = taxonomy_term_load_multiple(array($actuers[$i]['tid']));
             print '<li class="field-item ' . $class . '">' . $actuers_term->name . '</li>';
           }
          ?>
          </ul>
          </div>
          </div>
          </div>
    <?php endif; ?>
    <?php if (!empty($node->field_om_duration['und'][0]['value'])): ?>
            <div class="om-right-block">
             <h3 class="om-right-title"><?php print t("Duration estimate");?></h3>
             <div class="om-right-content duration"><?php print $node->field_om_duration['und'][0]['value'];?></div>
            </div>
            <?php endif; ?>
            <?php if (!empty($node->field_om_material['und'][0]['value'])): ?>
              <div class="om-right-block">
             <h3 class="om-right-title"><?php print t("Material Necessary");?></h3>
             <div class="om-right-content material"><?php print $node->field_om_material['und'][0]['value'];?></div>
            </div>
            <?php endif; ?>
            <?php  global $user;
             if(isset($node->uid)){
                $uid = $node->uid;
                $user_fields = user_load($node->uid);
                $fullname = '';
                if (isset($user_fields->field_full_name['und'][0]['value'])) {
                          $fullname = $user_fields->field_full_name['und'][0]['value'];
                }
             } 
                  ?>
            <?php if (!empty($fullname)): ?>
              <div class="om-right-block">
             <h3 class="om-right-title"><?php print t("Auters the procedure"); $fullname = '';?></h3>
             <div class="om-right-content actuers"><?php print $fullname;?></div>
            </div>
            <?php endif; ?>
            <?php if (!empty($node->field_om_experts['und'][0]['value'])): ?>
              <div class="om-right-block">
             <h3 class="om-right-title"><?php print t("Experts the procedure");?></h3>
             <div class="om-right-content experts"><div class="field field-name-field-om-experts field-type-list-text field-label-hidden view-mode-full"><div class="field-items">
             <?php 
             for ($i=0; $i<count($node->field_om_experts['und']); $i++) {
             if ($i % 2 == 0) {
               $class = "even";
             }
             else {
               $class = "odd";
             }
             print '<li class="field-item ' . $class . '">' . $node->field_om_experts['und'][$i]['value'] . '</li>';
            }
             ?>
             
             </div></div></div>
            </div>
            <?php endif; ?>
            <?php if (!empty($node->field_om_publication_period['und'][0]['value2'])): ?>
            <div class="om-right-block">
             <h3 class="om-right-title"><?php print t("End date of the validity");?></h3>
             <div class="om-right-content end-date"><?php
              $end_date = strtotime(substr($node->field_om_publication_period['und'][0]['value2'], 0, 10)); 
              print $end_date = format_date($end_date,'custom','l j F Y');?>
            </div></div>
            <?php endif; ?>
            <?php if (!empty($node->field_om_status['und'][0]['value'])): ?>
            <div class="om-right-block">
             <h3 class="om-right-title"><?php print t("Ciblage");?></h3>
             <div class="om-right-content om-status"><div class="field field-name-field-om-status field-type-list-text field-label-hidden view-mode-full"><div class="field-items">
             <?php 
             for ($i=0; $i<count($node->field_om_status['und']); $i++) {
             if ($i % 2 == 0) {
               $class = "even";
             }
             else {
               $class = "odd";
             }
             print '<li class="field-item ' . $class . '">' . $node->field_om_status['und'][$i]['value'] . '</li>';
            }
            ?>
             </div></div></div>
            </div>
            <?php endif; ?>
            <?php if (!empty($node->field_om_attachments['und'][0]['fid'])): ?>
            <div class="om-right-block">
             <h3 class="om-right-title"><?php print t("Documents");?></h3>
             <div class="om-right-content om-attachments">
             <?php //print str_replace('<a', '<a target="_blank"', $node->field_om_attachments);?>
                 <div class="field field-name-field-om-attachments field-type-file field-label-hidden view-mode-full">
									<div class="field-items">
									<?php 
									for ($i=0; $i<count($node->field_om_attachments['und']); $i++) {
			             if ($i % 2 == 0) {
			               $class = "even";
			             }
			             else {
			               $class = "odd";
			             }
			             ?>
			             <div class="field-item <?php print $class?>">
                  <span class="file">
                  <img class="file-icon" src="/modules/file/icons/application-octet-stream.png" title="" alt="">
                  <a href="" target="_blank"><?php print $node->field_om_attachments['und'][$i]['filename'];?></a>
                  </span>
                  </div>
			             <?php
			            }
									?>
									</div>
									</div>
             </div>
            </div>
            <?php endif; ?>
        </div>
        <div class="om-cont-holder">
        <?php if (!empty($node->field_om_objective['und'][0]['value'])) {?>
              <h4><?php print t('Objective');?></h4>
            <p><?php print $node->field_om_objective['und'][0]['value'];?></p>
            <?php }?>
            <?php if (!empty($node->body['und'][0]['value'])) {?>
              <h4><?php print t('Summary');?></h4>
                  <div class="om-body-content"><div class="h2-head-lines"></div><?php print $node->body['und'][0]['value'];?></div>
                  <?php }?>
       </div>
    </div>
    </div>