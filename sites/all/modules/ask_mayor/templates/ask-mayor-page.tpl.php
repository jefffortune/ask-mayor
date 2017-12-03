<div>
  <?php if($ask_mayor_image) : ?>
    <div class="mayor-image">
      <img src="<?php print $ask_mayor_image ?>" alt="Image of the mayor">
    </div>
  <?php endif; ?>
  <?php if($ask_mayor_body['value']) : ?>
    <div class="mayor-body">
      <?php print $ask_mayor_body['value'] ?>
    </div>
     <?php endif; ?>
    <?php print $question_form ?>
    <?php print $teaser_block ?>
    <?php if($archive_block !== FALSE) : ?>
        <?php print $archive_block ?>
    <?php endif; ?>
</div>
