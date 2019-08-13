<?php

/**
 * Service containers should extend this class.
 *
 * Child classes should define "create_[serviceClassName] methods that should
 * simply return an instance of the service class.
 */
abstract class AbstractPPContainer {

  /**
   * This array holds all services.
   * @var array
   */
  private $services = array();

  protected static $instances = null;

  protected function __construct() {}

  public static function getInstance() {
    $class = get_called_class();
    if (empty(self::$instances[$class])) {
      self::$instances[$class] = new $class;
    }
    return self::$instances[$class];
  }

  /**
   * Magic method that is triggered when someone calls $container->$name.
   *
   * @param string $name
   *   The machine name of the service.
   *   Must be a valid PHP identifier, without commas and such.
   *
   * @return object
   */
  function __get($name) {
    return isset($this->services[$name]) ? $this->services[$name]
        : $this->services[$name] = $this->createService($name);
  }

  /**
   * @param string $name
   *
   * @return object
   *   The service.
   * @throws Exception
   */
  protected function createService($name) {
    // Skip when called by the Devel or Search Krumo modules.
    if (strpos($name, 'krumo') === 0) {
      return;
    }
    if (class_exists($name)) {
      return new $name();
    }
    throw new Exception(t('Unknown service @name.', array('@name' => $name)));
  }

}
