<?php 
  /*print '<pre>';
  print_r($news_bencchmark_details);
  print '</pre>';  exit;*/
if(arg(0) == 'agenda-day') :	
?>

<div class="news-benchmark-grouping-content">      
   <?php foreach($news_bencchmark_details as $type => $details) { ?>     
    <div class="views-field views-field-rendered-entity">             
      <span class="field-content">
       <div class="agendatype-News ">
       <h2><?php print t(ucfirst($type)); ?></h2>
       </div>
       <?php foreach($details as $r => $res) { ?>
        <div class="agendatype-detailnews">
        <div class="views-row-1 views-row-odd views-row-first">             
          <div class="agenda-today-sec1">
            <div class="action_title"> <a title="" class="ctools-use-modal ctools-modal-ctools-sample-style ctools-use-modal-processed" href="/agenda-detail/day/nojs/1"><?php print $res['title']; ?></a> :</div>
            <?php if(!empty($res['body'])) :?>
            <div class="action_body"><?php print $res['body']; ?></div>
            <?php endif; ?>
            <?php if(!empty($res['attachment'])) : ?>
            <div class="action_attachment">
              <?php print $res['attachment'];?>
            </div>
            <?php endif;?>
          </div>
          </div>
      </div>
      <?php } ?> 
      </span>  
      
     
     
   </div>  
   <?php }?>  
</div>
<?php endif; ?>