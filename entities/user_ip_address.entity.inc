<?php
/**
 * @file
 * User IP Address class and interface.
 */

/**
 * UserIpAddress extends Entity.
 *
 * We need to create an Entity in order to use Views Bulk Actions on tracked
 * User IP addresses.
 */
class UserIpAddress extends Entity {

  /**
   * Implements EntityInterface::id().
   */
  public function id() {
    return isset($this->id) ? $this->id : NULL;
  }

  /**
   * Implements EntityInterface::entityType().
   */
  public function entityType() {
    return 'user_ip_address';
  }

  /**
   * Implements EntityInterface::bundle().
   */
  public function bundle() {}

  /**
   * Implements EntityInterface::label().
   */
  public function label() {}

  /**
   * Implements EntityInterface::uri().
   */
  public function uri() {}
}
