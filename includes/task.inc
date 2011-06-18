<?php
/**
 * @file
 * Include file containing the og_task class.
 */

class og_task {
  public $title = '';
  public $description = '';
  public $required = FALSE;
  public $completed = FALSE;
  public $callback = NULL;
  
  public function __construct($options = array()) {
    foreach ($options as $key => $value) {
      if (property_exists($this, $key)) {
        $this->$key = $value;
      }
    }
  }

  public function get_status() {
    $status = ($this->completed ? OG_TASKS_COMPLETED : ($this->required ? OG_TASKS_REQUIRED : OG_TASKS_OPTIONAL));
    return $status;
  }

  public function execute($entity, &$context) {
    if ($this->completed) {
      return FALSE;
    }

    if (is_callable($this->callback)) {
      debug(__FUNCTION__);
      call_user_func($this->callback, $entity, $this, $context);
    }
    else {
      debug($this->callback, 'not callable');
    }
  }
}
