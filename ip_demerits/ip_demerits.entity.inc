<?php
/**
 * @file
 * IP Demerit base class and interface.
 */

/**
 * IpDemeritEntity extends Entity.
 *
 * A subclass of Entity is a requirement for creating a custom entity. It is
 * also a minimum requirement to define the methods included here, even as
 * empty functions.
 */
class IpDemeritEntity extends Entity {

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
    return 'ip_demerit';
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
