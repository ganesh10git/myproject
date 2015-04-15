<div class="agenda-day-navigator-block">
<span class="agenda-day-text-title">Messages</span>
</div>
<div class="agenda-day-content-wrapper">
<?php
	foreach($result as $message_data) :?>  
	     <?php print $message_data['message_desc']?>
	<?php endforeach;?>
</div>
<div class="agenda-day-bottom">
<span class="close-pop close">Close</span>
</div>