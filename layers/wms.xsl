<xsl:stylesheet version="1.0" xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>
  <xsl:template match="//WMT_MS_Capabilities/Service">
  <h2>Server Properties</h2>
    <dl>
      <dt>WMS version</dt>
      <dd><xsl:value-of select="parent::*/@version" /></dd>
      <xsl:for-each select="child::*">
        <xsl:call-template name="serverinfo" />
      </xsl:for-each>
    </dl>
  </xsl:template>

  <xsl:template match="//WMT_MS_Capabilities/Capability">
    <h2>Possible Requests</h2>
    <xsl:for-each select="Request/child::*">
      <xsl:call-template name="request" />
    </xsl:for-each>
    <h2>Exceptions</h2>
    <xsl:for-each select="Exception/child::*">
      <xsl:call-template name="request" />
    </xsl:for-each>
    <h2>Vendor-specific capabilities</h2>
    <xsl:for-each select="VendorSpecificCapabilities/child::*">
      <xsl:call-template name="request" />
    </xsl:for-each>
    <h2>User-defined Symbolization</h2>
    <xsl:for-each select="UserDefinedSymbolization/child::*">
      <xsl:call-template name="request" />
    </xsl:for-each>
    <h2>Layers (<xsl:value-of select="Layer/Title" />)</h2>
    <p>Base SRS: <i><xsl:value-of select="Layer/SRS" /></i></p>
    <!-- AuthorityURL -->
    <xsl:for-each select="Layer/child::Layer">
      <xsl:call-template name="layers" />
    </xsl:for-each>
  </xsl:template>

  <xsl:template name="serverinfo">
    <xsl:choose>
      <xsl:when test="name()='Title'">
        <dt>Title</dt>
        <dd><xsl:value-of select="." /></dd>
      </xsl:when>
      <xsl:when test="name()='Abstract'">
        <dt>Abstract</dt>
        <dd><xsl:value-of select="." /></dd>
      </xsl:when>
      <xsl:when test="name()='KeywordList'">
        <dt>Keywords</dt>
        <dd><xsl:for-each select="child::*">
        <xsl:value-of select="." />
        <xsl:if test="not (position()=last())">, </xsl:if>
        </xsl:for-each>
        </dd>
      </xsl:when>
      <xsl:when test="name()='ContactInformation'">
        <dt>Contact</dt>
        <dd>
          <xsl:value-of select="ContactPersonPrimary/ContactPerson" />
          <xsl:if test="boolean(ContactPersonPrimary/ContactOrganization)"> (<xsl:value-of select="ContactPersonPrimary/ContactOrganization" />)</xsl:if>
          EMAIL: TODO
        <address>
        <xsl:value-of select="ContactAddress/Address" /><br />
        <xsl:value-of select="ContactAddress/City" />, <xsl:value-of select="ContactAddress/StateOrProvince" /><xsl:text> </xsl:text><xsl:value-of select="ContactAddress/PostCode" /><br/>
        <xsl:value-of select="ContactAddress/Country" />
        </address>
<!--        <div test="boolean(ContactElectronicMailAddress)"><xsl:text><div class="">Email: </xsl:text><xsl:value-of select="ContactElectronicMailAddress" /><xsl:text></div></xsl:text></xsl:if>
        <div test="boolean(ContactVoiceTelephone)"><xsl:text><div class="">Phone: </xsl:text><xsl:value-of select="ContactVoiceTelephone" /><xsl:text></div></xsl:text></xsl:if>
        <div test="boolean(ContactFacsimileTelephone)"><xsl:text><sl:text class="">Fax: </xsl:text><xsl:value-of select="ContactFacsimileTelephone" /><xsl:text></div></xsl:text></xsl:if>-->
        </dd>
      </xsl:when>
      <xsl:when test="name()='Fees'">
        <dt>Fees</dt>
        <dd><xsl:value-of select="." /></dd>
      </xsl:when>
      <xsl:when test="name()='AccessConstraints'">
        <dt>Access Constraints</dt>
        <dd><xsl:value-of select="." /></dd>
      </xsl:when>
    </xsl:choose>
  </xsl:template>

  <xsl:template name="request">
  </xsl:template>

  <xsl:template name="exceptions">
  </xsl:template>

  <xsl:template name="vendorspecificcapabilities">
  </xsl:template>

  <xsl:template name="userdefinedsymbolization">
  </xsl:template>

  <xsl:template name="layers">
    <div><xsl:value-of select="Name" /> (<xsl:value-of select="Title" />)</div>
  </xsl:template>

</xsl:stylesheet>