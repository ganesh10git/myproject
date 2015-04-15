<?php 
  $image_pros = '';
  
  if(isset($field_sp_image_pros[0]['url'])) {
    $sales_image = array(
  	  'style_name'=> 'im_sales_plan_content_image',
  	  'path' => $field_sp_image_pros[0]['url'],//http://portal.im.dev.carrefour.com/sites/default/files/laptop2.jpg
      'alt' => $title,
      'title' => $title,
  	//'attributes' => array('id' => 'sales-img'),      
    );
    $image_pros = theme('image_style', $sales_image);
  }
  $title = $title;  
?>

<div class="sales-plan-content-wrapper">
   <div id="sp_link_container" class="white_content">
   <a class="spl_link_close" href = "javascript:void(0)" onclick = "document.getElementById('sp_link_container').style.display='none';"><?php print t("Close");?></a>
      <span class="sp_heading"><?php print t("Link to Sales plan:");?></span><br />
      <span class="sp_text"><?php print t("Here is the link to the current salesplan:");?><br /></span><br />
      <p class="sp_link"><?php print $sp_copy;?></p>
      <button class="spl_link_ok"  onclick = "document.getElementById('sp_link_container').style.display='none';" type="button"><?php print t("Ok");?></button>
 </div>
  <div class="sales-title"><?php  print $title ?></div>
  <a id="clipboard" href = "javascript:void(0);" onclick = "document.getElementById('sp_link_container').style.display='block';" title="<?php print $sp_copy;?>"><?php print t("Create a link to Salesplan");?></a>
  <div class="sales-data">
    <div class="sales-data-right-content">
      <?php if(!empty($image_pros)) { ?>
          <div class="sales-image">
              <?php print '<div class="file-link">' . $image_pros . '</div>';?>
          </div>
      <?php } ?>
		<div class="sales-date-description">
			<div class="sales-date-range">
			   <span class="label">Période de commande:</span>
			   <?php if(isset($field_sp_order_period_startdate)) :?>
			   <span class="date-range"> <?php print $field_sp_order_period_startdate .' '.t('to') .' '. $field_sp_order_period_enddate?></span>
			   <?php endif; ?>
			</div>
			<div class="sales-description">
			<?php print isset($body) ? $body : '' ;?>
			</div>
		 </div>
    	<div class="sales-attachments">
    		<div class="sales-attachments-left-set">


	      <!--</div>
	      <div class="sales-attachments-left-set">-->
          <?php
	        $plv_text = variable_get('im_admin_sales_plan_plv', 'PLV');
	        if(sizeof($field_sp_plv) > 0){ ?>
	        <div class="sales-plv">
	        <div class="attachment-title"><?php print t($plv_text);?></div>
	          <div class="attachment-body">        
			        <?php 
			        if(!empty($field_sp_plv)) {
			          foreach ($field_sp_plv as $document_link) {
			                print '<div class="file-link"><a href="/check_file_access/'. $document_link['file_id'].'" target ="_blank" onclick="return xt_click(this, \'C\',\'3\',\'download::sales_plan::'.str_replace(" ","_",rawurlencode(rawurldecode($document_link['name']))).'\',\'A\')">' . $document_link['name'] . '</a></div>';
			           } 
			        }
			        else{
			        	print t('No document available');
			        }
			        ?>
	        	</div>
	        </div>

	        <?php 
	        }
	        $visual_text = variable_get('im_admin_sales_plan_visual', 'Visual');
	        if(sizeof($field_sp_visual) > 0){ ?>
	        <div class="sales-visuel">
	          <div class="attachment-title"><?php print t($visual_text);?></div>
	          <div class="attachment-body">        
			        <?php
			        if(!empty($field_sp_visual)){
			            foreach ($field_sp_visual as $document_link) {
			            	print '<div class="file-link"><a href="/check_file_access/'. $document_link['file_id'].'" target ="_blank" onclick="return xt_click(this, \'C\',\'3\',\'download::sales_plan::'.str_replace(" ","_",rawurlencode(rawurldecode($document_link['name']))).'\',\'A\')">' . $document_link['name'] . '</a></div>';
			          } 
			        }
			        else{
		            print t('No document available');
		          }
			        ?>
	        	</div>
	        </div>
	       
	        <?php 
	        }
          $catalogue_text = variable_get('im_admin_sales_plan_catalogue', 'Catalogue');
          if(sizeof($field_sp_catalogue) > 0){ ?>
          <div class="sales-catalogue">
          <div class="attachment-title"><?php print t($catalogue_text);?></div>
            <div class="attachment-body"> 
          <?php 
          if(!empty($field_sp_catalogue)){
              foreach ($field_sp_catalogue as $document_link) {
               print '<div class="file-link"><a href="/check_file_access/'. $document_link['file_id'].'" target ="_blank" onclick="return xt_click(this, \'C\',\'3\',\'download::sales_plan::'.str_replace(" ","_",rawurlencode(rawurldecode($document_link['name']))).'\',\'A\')">' . $document_link['name'] . '</a></div>';
            }
          }
           else{
            print t('No document available');
          }
          ?>
           </div>
          </div>
          <?php }
	        $others_text = variable_get('im_admin_sales_plan_others', 'Others');
	        if(sizeof($field_sp_others) > 0){ ?> 
	        <div class="sales-autre">
	        <div class="attachment-title"><?php print t($others_text);?></div>
	          <div class="attachment-body"> 
			        <?php
			        if(!empty($field_sp_others)){
			           foreach ($field_sp_others as $document_link) {
			             print '<div class="file-link"><a href="/check_file_access/'. $document_link['file_id'].'" target ="_blank" onclick="return xt_click(this, \'C\',\'3\',\'download::sales_plan::'.str_replace(" ","_",rawurlencode(rawurldecode($document_link['name']))).'\',\'A\')">' . $document_link['name'] . '</a></div>';
			          } 
			          }
			          else{
		            print t('No document available');
		          }
			        ?>
	        	</div>
	        </div>
	      </div>
	       <?php 
	       }
	        $help_control_text = variable_get('im_admin_sales_plan_help_control', 'Help Control'); 
          if(sizeof($field_sp_help_control) > 0){ ?>
          <div class="sales-aide">
            <div class="attachment-title"><?php print t($help_control_text);?></div>
            <div class="attachment-body">
            <?php   
              if(!empty($field_sp_help_control)){
                foreach ($field_sp_help_control as $document_link) {
                  print '<div class="file-link"><a href="/check_file_access/'. $document_link['file_id'].'" target ="_blank" onclick="return xt_click(this, \'C\',\'3\',\'download::sales_plan::'.str_replace(" ","_",rawurlencode(rawurldecode($document_link['name']))).'\',\'A\')">' . $document_link['name'] . '</a></div>';
                }
              }
              else {
                 print t('No document available');
              }
             ?>
             </div>
          </div>
          <?php 
          }?>
	    </div>
    </div>
  </div>
</div>
