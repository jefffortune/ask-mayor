
<h1><?php print $subject ?></h1>
<div>Asked: <?php print format_date($created, 'custom', 'd/M/y')?></div>
<div>Last updated: <?php print format_date($updated, 'custom', 'd/M/y')?></div>
<h3><?php print $question ?></h3>
<div class="response">
  <?php print $response ?>
  <?php if (isset($_GET['destination'])) : ?>
    <div class="back">
      <?php print l(t('Back'), variable_get('ask_mayor_main_page_path', 'ask-the-mayor')) ?>
    </div>
  <?php endif; ?>
</div>