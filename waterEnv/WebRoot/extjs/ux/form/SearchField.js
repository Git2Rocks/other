/*
 * ! Ext JS Library 3.2.0 Copyright(c) 2006-2010 Ext JS, Inc.
 * licensing@extjs.com http://www.extjs.com/license
 */
/**
 * @class Ext.ux.form.SearchField
 *        ��ѯ����򡣿����ڶ�Grid��Store�Ĳ�ѯ���û����������󣬵����ѯ��Ť����ʹ�ûس���ʱ�����������Store��baseParams�м����û�����Ĳ�ѯ������������Store��reload������
 *
 * <pre><code>
 *            ...
 *            var o = {
 * 				start : 0
 * 			};
 *        this.store.baseParams = this.store.baseParams || {};
 *        this.store.baseParams[this.paramName] = v;
 *        this.store.reload({
 * 				params : o
 * 			});
 *            ...
 * </code>
 * v Ϊ�û������ֵ
 * </pre>
 *
 * @extends Ext.form.TwinTriggerField
 */
Ext.define('Ext.ux.form.SearchField', {
    extend: 'Ext.form.TwinTriggerField',
    /**
     * @cfg {Ext.data.Store} store �󶨲�ѯ��Store
     */
    initComponent: function () {
        this.callParent(arguments);
        this.on('specialkey', function (f, e) {
            if (e.getKey() == e.ENTER) {
                this.onTrigger2Click();
            }
        }, this);
    },

    validationEvent: false,
    validateOnBlur: false,
    trigger1Cls: Ext.baseCSSPrefix + 'form-clear-trigger',

    trigger2Cls: Ext.baseCSSPrefix + 'form-search-trigger',
    width: 180,
    hasSearch: false,
    /**
     * @cfg {String} paramName
     *      �൱��Field��name���ԣ�ָ���ò�ѯ���͵���̨ʱʹ�õ����ơ���Ĭ��Ϊ"query"������̨ʹ��request.getParameter("query")�ɻ���û�����Ĳ�ѯ������
     */
    paramName: 'query',

    afterRender: function(){
        this.callParent();
        this.triggerCell.item(0).setDisplayed(false);
    },
    onTrigger1Click: function () {
        if (this.hasSearch) {
            this.setValue('');
            var o = {
                start: 0
            };
            this.store.getProxy().extraParams = this.store.getProxy().extraParams || {};
            this.store.getProxy().extraParams[this.paramName] = '';
            this.store.reload({
                params: o
            });
            this.triggerCell.item(0).setDisplayed(false);
            this.hasSearch = false;
        }
    },

    onTrigger2Click: function () {
        var v = this.getRawValue();
        if (v.length < 1) {
            this.onTrigger1Click();
            return;
        }
        var o = {
            start: 0
        };
        this.store.getProxy().extraParams = this.store.getProxy().extraParams || {};
        this.store.getProxy().extraParams[this.paramName] = v;
        this.store.reload({
            params: o
        });
        this.hasSearch = true;
        this.triggerCell.item(0).setDisplayed(true);
    }
});