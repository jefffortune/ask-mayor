
<div class="archvie">
  <?php foreach ($rows as $row) : ?>
    <div class="row">
      <?php print $row ?>
    </div>
  <?php endforeach; ?>
  <?php if(isset($_GET['destination'])) : ?>
      <div class="back">
        <?php print l(t('Back'), variable_get('ask_mayor_main_page_path', 'ask-the-mayor')) ?>
      </div>
  <?php endif; ?>
</div>